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

#ifndef da_i2c_sensor_h
#define da_i2c_sensor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "da_types.h"
#include "da_sensor.h"
#include "Arduino.h"

#define TIMEOUT_MS	3000 /* 3 seconds */
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_i2c_sensor: public da_sensor {
private:
	uchar bus_addr;						/* bus address */
	uchar who_am_i;						/* id register address */
protected:
	int ReadRegisters(uchar addr, uint bytes, uchar *dest);
	byte ReadRegister(uchar addr);
	void WriteRegister(uchar addr, uchar data);
public:
	da_i2c_sensor(uchar addr, uchar whoami, uint rate = 1, uint maxrate = 1): 
	bus_addr(addr), who_am_i(whoami), da_sensor(rate, maxrate) { }
	
	virtual void Connect(void) { }
	virtual void Disconnect(void) { }
	virtual void Calibrate(void) = 0;
	virtual void SetRate(uint) = 0;
	virtual void Sample(void) = 0;
};

#endif