/*
 * connection_test.ino
 * ---------------------------------------------------------------------------
 * Minimal sketch to confirm that the computer can upload to the board and talk
 * to it. Run this FIRST, before any sensor sketch. It needs no external components.
 *
 * HOW TO USE
 *   1. Disconnect all wiring; leave only the Arduino and the USB cable.
 *   2. Tools -> Board -> Arduino Uno
 *   3. Tools -> Port -> the port that appears only when the board is plugged in
 *   4. Upload, then open Tools -> Serial Monitor at 9600 baud.
 *
 * IT WORKS IF: the small LED marked "L" on the board blinks once per second,
 * and the Serial Monitor prints an increasing number of seconds.
 *
 * ---------------------------------------------------------------------------
 */

const int led = 13;   // The Uno has an LED soldered to pin 13, marked "L"

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.println("Arduino connected!");
}

void loop() {
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  Serial.print("Uptime (s): ");
  Serial.println(millis() / 1000);
}
