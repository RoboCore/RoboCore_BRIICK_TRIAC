#ifndef BRIICK_TRIAC_H
#define BRIICK_TRIAC_H

/*******************************************************************************
* RoboCore BRIICK TRIAC Library (v1.0)
* 
* Library to use the BRIICK TRIAC v1.0.
* 
* Copyright 2025 RoboCore.
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

#define BRIICK_TRIAC_DEBUG

// --------------------------------------------------
// Libraries

#include <stdint.h>

#include <Wire.h>

#ifdef BRIICK_TRIAC_DEBUG
#include <Stream.h>
#endif

// --------------------------------------------------
// Macros

#ifndef HIGH
#define HIGH (1)
#define LOW (0)
#endif

#define TRIAC_ADDRESS (0x25) // default address

#define TRIAC_REGISTER_INPUT   (0x00)
#define TRIAC_REGISTER_OUTPUT  (0x01)
#define TRIAC_REGISTER_CONFIG  (0x03)

#define TRIAC_DRIVER  (0x01)

// --------------------------------------------------
// Class - BRIICK TRIAC

class BRIICK_TRIAC {
  public:
    BRIICK_TRIAC(TwoWire &);
    BRIICK_TRIAC(TwoWire &, uint8_t);

    bool config(bool = false);
    uint8_t getState(void);
    bool off(void);
    bool on(void);
  
#ifdef BRIICK_TRIAC_DEBUG
    void setDebugger(Stream &);
#endif

  private:
    TwoWire * _i2c;
    uint8_t _address;
    bool _initialized;
    uint8_t _state;

#ifdef BRIICK_TRIAC_DEBUG
    Stream * _debugger;
#endif

  bool _setState(uint8_t);
};

// --------------------------------------------------

#endif // BRIICK_TRIAC_H
