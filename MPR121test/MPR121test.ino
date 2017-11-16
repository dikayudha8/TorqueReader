/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t capValueBefore = 0;
uint16_t minimumValue, touched = 50;
void setup() {
  Serial.begin(9600);
 
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  pinMode(13, OUTPUT);
  for (uint8_t i = 0; i < 100; ++i)
    minimumValue = cap.filteredData(1);

  uint16_t raw[128];
  for (uint8_t i = 0; i < 128; ++i) {
    raw[i] = cap.filteredData(1);
    if (minimumValue > raw[i] )
      minimumValue = raw[i];
  }

}

void loop() {
  int16_t delta = cap.filteredData(1);// - capValueBefore;
//  Serial.print(delta);
//  Serial.print("\t");
//  Serial.println(minimumValue - touched);

  if (delta <= (minimumValue - touched)) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(50);
}
