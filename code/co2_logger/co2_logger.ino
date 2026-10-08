/*
 * co2_logger.ino
 * ---------------------------------------------------------------------------
 * 
 * Reads CO2 concentration from an MH-Z19 NDIR sensor every 10 seconds and
 * appends each reading to data.csv on an SD card.
 *
 * Wiring: see ../../hardware/wiring.md
 * Walkthrough of what every line does: see ../README.md
 *
 * Output format (data.csv):
 *     Time (seconds),CO2 (ppm)
 *     10,412
 *     20,415
 *
 * KNOWN LIMITATION: the time column counts successful readings
 * (lineCounter * 10 s). It is not wall-clock time. A failed reading writes no
 * row, so every later timestamp under-reports the true elapsed time.
 * ---------------------------------------------------------------------------
 */

#include <SPI.h>             // SPI bus, used by the SD card reader
#include <SD.h>              // File handling on the SD card
#include <SoftwareSerial.h>  // Emulates a serial port on ordinary digital pins

// --- Pin assignments -------------------------------------------------------
// Only CS is configurable; MOSI/MISO/SCK are fixed at pins 11/12/13 on an Uno
// and are driven by SPI.h without appearing in this sketch.
const int chipSelect = 10;

// These names are from the ARDUINO's point of view:
// pin 6 is where the Arduino receives, so it wires to the SENSOR's TX pin.
#define MH_Z19_RX 6
#define MH_Z19_TX 7

// Built-in LED on the Uno. WARNING: pin 13 is also the SPI clock (SCK).
const int statusLed = 13;

// Sampling interval in milliseconds. 1000 ms = 1 s.
const int time_step = 1000;

// --- Objects and global state ---------------------------------------------
// A second, software-emulated serial port dedicated to the sensor, so that the
// hardware port stays free for debug output.
SoftwareSerial co2Serial(MH_Z19_RX, MH_Z19_TX);

// The 9-byte "read CO2 concentration" command defined in the MH-Z19 datasheet.
// These values are not arbitrary and must not be changed.
byte cmd[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

// Buffer for the sensor's 9-byte reply.
unsigned char response[9];

File myFile;                    // Handle for the open file on the SD card
unsigned long lastLogTime = 0;  // millis() value at the previous reading
int lineCounter = 1;            // Number of data rows written so far

// ===========================================================================
// setup() runs once, when the board is powered on or reset.
// ===========================================================================
void setup() {
  Serial.begin(9600);  // Open USB serial for debug output at 9600 baud

  pinMode(statusLed, OUTPUT);  // Declare pin 13 as an output before writing to it

  Serial.println("--- SYSTEM STARTUP ---");

  // --- Initialise the SD card ---
  Serial.print("Initializing SD card... ");
  if (!SD.begin(chipSelect)) {
    Serial.println("FAILED!");
    // Halt here: without the SD card there is nowhere to store data.
    // Comment out the next line if you want to test the sensor alone, but note
    // that the "SUCCESS!" message below will then print even after a failure.
    while (1);
  }
  Serial.println("SUCCESS!");

  // --- Create data.csv with a header row, if it does not exist yet ---
  // If it DOES exist, nothing is deleted: new rows are appended below the old
  // data and the time column restarts at 10. 
  if (!SD.exists("data.csv")) {
    myFile = SD.open("data.csv", FILE_WRITE);
    if (myFile) {
      myFile.println("Time (seconds),CO2 (ppm)");
      myFile.close();  // Closing is what actually commits the write
      Serial.println("Created new data.csv file.");
    }
  } else {
    Serial.println("Found existing data.csv file.");
  }

  // --- Open the link to the sensor ---
  co2Serial.begin(9600);  // The MH-Z19 communicates at 9600 baud
  Serial.println("Ready! Starting loop...\n");
}

// ===========================================================================
// loop() repeats forever after setup() finishes.
// ===========================================================================
void loop() {
  // Timer: compare the current uptime against the last reading
  if (millis() - lastLogTime >= time_step) {
    lastLogTime = millis();

    Serial.print("[Loop] Requesting CO2 data... ");

    // Discard anything left in the receive buffer from a previous exchange,
    // so that the reply we read next is definitely the reply to this request.
    while (co2Serial.available()) { co2Serial.read(); }

    co2Serial.write(cmd, 9);  // Send the 9-byte read command
    delay(150);               // Give the sensor time to answer

    int availableBytes = co2Serial.available();
    Serial.print("Bytes received: ");
    Serial.print(availableBytes);
    Serial.print(" / 9. ");

    if (availableBytes >= 9) {
      // Copy the reply into the response buffer, one byte at a time
      for (int i = 0; i < 9; i++) {
        response[i] = co2Serial.read();
      }

      // Sanity check: a valid MH-Z19 reply always starts with 0xFF 0x86.
      if (response[0] == 0xFF && response[1] == 0x86) {

        // The concentration arrives as two bytes: a high byte and a low byte.
        // Shifting the high byte left by 8 bits multiplies it by 256; adding
        // the low byte reassembles the 16-bit value.
        int co2ppm = (response[2] << 8) + response[3];

        // Elapsed time is INFERRED from the number of readings, not measured.
        int secondsPassed = lineCounter * (time_step / 1000);

        Serial.print("CO2: ");
        Serial.print(co2ppm);
        Serial.print(" ppm. Writing to SD... ");

        // Open, write, close on every reading.
        myFile = SD.open("data.csv", FILE_WRITE);
        if (myFile) {
          myFile.print(secondsPassed);
          myFile.print(",");
          myFile.println(co2ppm);
          myFile.close();

          lineCounter++;
          Serial.println("DONE!");

          // Visual confirmation that a row was stored by blinking the built-in LED.
          digitalWrite(statusLed, HIGH);
          delay(150);
          digitalWrite(statusLed, LOW);
        } else {
          Serial.println("SD WRITE ERROR!");
        }
      } else {
        Serial.println("ERROR: Bad data packet headers!");
      }
    } else {
      Serial.println("TIMEOUT: Sensor didn't reply in time.");
    }
  }
}
