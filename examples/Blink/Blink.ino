/*******************************************************************************
* RoboCore BRIICK TRIAC - Blink (v1.0)
* 
* Simple program to blink the driver of the BRIICK TRIAC.
* 
* Copyright 2025 RoboCore.
* Written by Francois (23/10/2024).
* 
* 
* This file is part of the BRIICK TRIAC library by RoboCore ("RoboCore-BRIICK-TRIAC-lib").
* 
* "RoboCore-BRIICK-TRIAC-lib" is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* "RoboCore-BRIICK-TRIAC-lib" is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public License
* along with "RoboCore-BRIICK-TRIAC-lib". If not, see <https://www.gnu.org/licenses/>
*******************************************************************************/

#include <Wire.h>
#include <BRIICK_TRIAC.h>

BRIICK_TRIAC triac(Wire);

const uint16_t DELAY_TIME = 2000; // [ms]

void setup() {
  // configure the I2C communication
  Wire.begin();

  // configure the serial communication
  Serial.begin(115200);

  // configure the BRIICK
  Serial.print("TRIAC config: ");
  Serial.println(triac.config());
}

void loop() {
  triac.on();
  delay(DELAY_TIME);
  triac.off();
  delay(DELAY_TIME);
}
