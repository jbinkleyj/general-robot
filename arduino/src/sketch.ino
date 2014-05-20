/*
   Generic Robot with obstacle avoidance capabilities
   Copyright (C) 2014  Joao Salavisa (joao.salavisa@gmail.com)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have readd a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Wire.h>

#define address 0x1E 

void setup() {
    Serial.begin(9600);

    Wire.begin();
    Wire.beginTransmission(address); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.endTransmission();

    Serial.println("Setup completed");
}

void loop() {
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(address);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(address, 6);    // Request 6 bytes; 2 bytes per axis
  if(Wire.available() <=6) {    // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
  
  // Print raw values

  float heading = atan2(y, x);
  if(heading < 0) 
      heading += 2*PI;


  float headingDegrees = heading * 180/M_PI; 
  Serial.print("  Heading: ");
  Serial.println(headingDegrees);

  delay(500);
}


