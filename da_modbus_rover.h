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
#ifndef da_modbus_rover_h
#define da_modbus_rover_h

#define MB_TIMEOUT	5000 /* milliseconds */
#define INVALID_IDX	-1

/* Modbus slave configuration parameters */
#define MB_SLAVE     1
#define MB_BAUD      57600
#define MB_PARITY    'e'
#define MB_TXENPIN   0

/******************************************************************************
 * Includes
 ******************************************************************************/
//#include <Arduino.h>
#include "da_types.h"
#include "da_rover_lmu.h"
#include <ModbusSlave.h>
 
/******************************************************************************
 * Classes
 ******************************************************************************/

/* everything is a 16 bit int as required by modbus */
struct mb_motor {
	int index;
	int direction;
	int throttle;
};

struct mb_switch {
	int index;
	int state;
};

struct mb_sensor {
	int index;
	int reg;
	int data;
};

struct mb_chassis {
	int throttle;
	int direction;
	struct fb_data xyz;
	int delta;
};

struct mb_rover {
	struct mb_motor motor;
	struct mb_switch sw;
	struct mb_sensor sensor;
	struct mb_chassis chassis;
};

/* FIXME: modbus rover _IS_A_ Modbus class and _IS_A_ rover_lmu */
class da_modbus_rover: public da_rover_lmu {
private:
//	int *regs;
	struct mb_rover *rover;
	long baudrate;
	byte registerCount;
	ModbusSlave mbs;
	unsigned long wdog, timeout;         /* watchdog */
	char chassisIdx, motorIdx, sensorIdx, switchIdx;
public:
	
  da_modbus_rover(
		  struct mb_rover *mb_rover,
		  byte registerCount,
		  long baudrate = MB_BAUD,
		  uint timeout = MB_TIMEOUT):\
  da_rover_lmu(),
  registerCount(registerCount),
  rover(mb_rover),
  mbs(),
  wdog(0),
  baudrate(baudrate),
  timeout(timeout) 
  { }

  virtual void Init(void);
  void Update(void);
};

#endif