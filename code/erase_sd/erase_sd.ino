/*
 * erase_sd.ino
 * ---------------------------------------------------------------------------
 * Deletes data.csv from the SD card.
 *
 * RUN THIS BEFORE EVERY NEW MEASUREMENT. The logger sketches append to an
 * existing data.csv rather than overwriting it, and their time column restarts
 * at 10 s on every boot. Without erasing, one file ends up containing two runs
 * with duplicate timestamps and, if you switched sensors, two different headers.
 *
 * Back up any data you care about before running this: the deletion cannot be
 * undone from the Arduino.
 *
 * ---------------------------------------------------------------------------
 */

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println(" failed!");
    while (1);
  }
  Serial.println(" done.");

  if (SD.exists("data.csv")) {
    Serial.print("Deleting data.csv... ");
    SD.remove("data.csv");
    Serial.println("DELETED SUCCESSFULLY!");
  } else {
    Serial.println("No data.csv file found on the card. It is already clean!");
  }
}

void loop() {
}
