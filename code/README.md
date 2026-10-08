# Code walkthrough

This page explains what every sketch does and why, aimed at someone who has
never written Arduino code before. Arduino uses a simplified dialect of **C++**.

## The sketches in this folder

| Sketch | Purpose | Run it when |
|---|---|---|
| `connection_test/` | Blinks the built-in LED and prints uptime | First, always|
| `erase_sd/` | Deletes `data.csv` | Before every new measurement run |
| `co2_logger/` | Logs CO₂ every 10 s to the SD card | Setup A |


Each sketch lives in its own folder with a matching name. This is a requirement
of the Arduino IDE, not a stylistic choice: a `.ino` file must sit inside a
folder of the same name or the IDE will not open it.

---

## Concepts you need before reading the code

**`setup()` and `loop()`.** Every Arduino sketch has exactly these two
functions. `setup()` runs once when the board is powered up or reset; `loop()`
then repeats forever until power is removed. There is no operating system and no
"exit".

**`Serial` vs `SoftwareSerial`.** Serial communication means sending data one bit
at a time over a single wire. The Uno has one *hardware* serial port, on pins 0
and 1, which is wired internally to the USB connector — that is the port
`Serial.println()` uses to reach the Serial Monitor. Because the CO₂ sensor also
speaks serial, and we want USB debugging at the same time, the sketch creates a
*second*, software-emulated port on pins 6 and 7 using the `SoftwareSerial`
library. Software emulation is slower and more timing-sensitive, which is fine
at 9600 baud with one reading every ten seconds.

**`pinMode`, `digitalWrite`.** A digital pin can either send a signal (`OUTPUT`)
or read one (`INPUT`). `pinMode(pin, OUTPUT)` declares the intent; only then does
`digitalWrite(pin, HIGH)` (≈5 V, LED on) or `digitalWrite(pin, LOW)` (0 V, LED
off) behave predictably. Pins default to `INPUT`, so the `pinMode` call is not
optional.

**`const int` vs `#define`.** `const int chipSelect = 10;` creates a read-only
variable. `#define MH_Z19_RX 6` is a *text substitution* performed before
compilation: every occurrence of `MH_Z19_RX` is literally replaced by `6`. Both
are used here; the difference rarely matters at this scale.

**`millis()`.** Returns the number of milliseconds since the board started. Used
for timing without blocking the program, unlike `delay()`.

---

## `co2_logger.ino`, block by block

### Global declarations

```cpp
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
```

Pulls in three libraries: the SPI bus protocol used by the SD reader, file
handling on the SD card, and the software-emulated serial port.

```cpp
const int chipSelect = 10;
```

The pin that selects the SD card on the SPI bus. Notice that MOSI, MISO and SCK
(pins 11, 12, 13) are never declared — their locations are fixed in the Uno's
hardware and `SPI.h` drives them automatically. Only chip-select is free to
choose.

```cpp
#define MH_Z19_RX 6
#define MH_Z19_TX 7
```

The two pins carrying the software serial port. The names are from the Arduino's
perspective: pin 6 is where the Arduino *receives*, so it is wired to the
sensor's *transmit* pin. See `hardware/wiring.md`.

```cpp
byte cmd[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
```

An array of nine bytes written in hexadecimal. This is the exact "read CO₂
concentration" command specified in the MH-Z19 datasheet; the final byte is its
checksum. These values are dictated by the sensor manufacturer and must not be
altered.

```cpp
unsigned char response[9];
```

An empty nine-slot buffer for the sensor's reply. `unsigned char` and `byte` are
the same thing: a number from 0 to 255.

```cpp
unsigned long lastLogTime = 0;
```

Stores when the last reading happened. `unsigned long` is used because `millis()`
grows large — it overflows only after about 49 days.

### `setup()`

Opens the USB serial link at 9600 baud, declares pin 13 an output, initialises
the SD card, creates `data.csv` with a header row if it does not already exist,
and opens the software serial link to the sensor.

The SD initialisation is guarded:

```cpp
if (!SD.begin(chipSelect)) {
  Serial.println("FAILED!");
  while (1);
}
```

`!` means "not", so this block runs when initialisation *fails*. `while (1);` is
an infinite loop that does nothing — it halts the board deliberately, because
there is no point logging data with nowhere to store it.

> **If you comment out `while (1);`** (which is convenient while testing the
> sensor without an SD card) the program continues and then prints `SUCCESS!`
> even though initialisation failed, because that message sits outside the `if`
> block. Be aware of this when reading the serial output.

The file-creation logic distinguishes two cases:

```cpp
if (!SD.exists("data.csv")) { ... } else { ... }
```

If the file is new, the header row is written. If it already exists, nothing is
deleted and the logger simply appends below the old data — with the time column
restarting at 10. This is why `erase_sd` exists.

### `loop()`

```cpp
if (millis() - lastLogTime >= time_step) {
```

"Have ten seconds passed since the last reading?" Using `millis()` this way
rather than `delay(10000)` keeps the board responsive between readings.

```cpp
while (co2Serial.available()) { co2Serial.read(); }
```

`available()` reports how many bytes are waiting to be read; `read()` consumes
one. This loop therefore throws away any stale bytes so that the reply read next
is unambiguously the reply to the request about to be sent.

```cpp
co2Serial.write(cmd, 9);
delay(150);
```

Send the nine-byte command, then wait 150 ms for the sensor to answer.

```cpp
for (int i = 0; i < 9; i++) {
  response[i] = co2Serial.read();
}
```

A `for` loop running nine times (`i` = 0…8), copying the reply into the buffer.

```cpp
if (response[0] == 0xFF && response[1] == 0x86) {
```

A validity check: a genuine MH-Z19 reply always begins with those two bytes.
`==` tests equality, `&&` means "and". Anything else indicates noise or a
desynchronised stream, and the sketch reports `Bad data packet headers!` rather
than logging nonsense.

```cpp
int co2ppm = (response[2] << 8) + response[3];
```

The concentration arrives split across two bytes. `<<` is a bit shift: moving
the high byte eight places left is the same as multiplying it by 256. Adding the
low byte reassembles the 16-bit value. This is the standard way to combine two
bytes into one number.

```cpp
int secondsPassed = lineCounter * (time_step / 1000);
```

**This is not a clock reading.** It multiplies the number of readings written so
far by the interval in seconds. If a reading fails, no row is written,
`lineCounter` does not advance, and the reported time falls behind reality. See
the limitations section of the main README.

```cpp
myFile = SD.open("data.csv", FILE_WRITE);
...
myFile.close();
```

The file is opened and closed on *every* reading. Closing is what actually
commits data to the card; keeping the file open across a whole run would risk
losing everything if power were cut mid-write.

```cpp
digitalWrite(statusLed, HIGH);
delay(150);
digitalWrite(statusLed, LOW);
```

A 150 ms blink of the built-in LED, confirming visually that a row was stored —
useful when the board is running on a powerbank with no computer attached.

The three `else` branches, in order, report: a failed SD write, an invalid reply
header, and a sensor that did not answer in time.


