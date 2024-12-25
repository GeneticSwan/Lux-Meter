#include <Wire.h>
#include <Adafruit_VEML7700.h>
#include <SD.h>

#define CS_PIN 10  // Chip Select pin for the SD card module

Adafruit_VEML7700 veml = Adafruit_VEML7700();

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize the VEML7700 sensor
  if (!veml.begin()) {
    Serial.println("VEML7700 not found!");
    while (1);
  }
  Serial.println("VEML7700 initialized!");

  // Initialize the SD card
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialized!");
}

void loop() {
  // Read lux value
  float lux = veml.readLux();
  Serial.print("Lux: ");
  Serial.println(lux);

  // Log to SD card
  File logFile = SD.open("lux_log.txt", FILE_WRITE);
  if (logFile) {
    logFile.print("Lux: ");
    logFile.println(lux);
    logFile.close();
    Serial.println("Logged to SD card.");
  } else {
    Serial.println("Error opening log file.");
  }

  delay(1000);  // Log every second
}
