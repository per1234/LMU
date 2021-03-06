/*
 This library provides the core organizational classes of the LocoMotionUnit 
 for Arduino based platforms.
 
 Copyright (C) 2013 Joshua Frkuska  DigitalArtisans.Org
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "da_i2c_sensor.h"
#include <Wire.h>

int da_i2c_sensor::ReadRegisters(uchar addr, uint bytes, uchar *dest)
{
  unsigned long now = millis();
  
  Wire.beginTransmission(bus_addr);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(bus_addr, bytes); //Ask for bytes, once done, bus is released by default

  while(Wire.available() < bytes) { //Hang out until we get the # of bytes we expect
	  if ((millis() - now) > TIMEOUT_MS) {
		  Serial1.print("I2C Timed out while reading\r\n");
		  return -E_TIMEOUT;
	  }
  }
  
  for(uint x = 0; x < bytes; x++)
    dest[x] = Wire.read();
  
  return 0;
}

byte da_i2c_sensor::ReadRegister(uchar addr)
{
  byte data = 0;
  ReadRegisters(addr, 1, &data);
  return data;
}

void da_i2c_sensor::WriteRegister(uchar addr, uchar data)
{
  Wire.beginTransmission(bus_addr);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission(); //Stop transmitting
}