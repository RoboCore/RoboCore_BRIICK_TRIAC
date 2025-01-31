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

// --------------------------------------------------
// Libraries

#include <BRIICK_TRIAC.h>

// --------------------------------------------------
// --------------------------------------------------

// Constructor (default)
//  @param (i2c) : the I2C/TWI bus used for communication [TwoWire]
BRIICK_TRIAC::BRIICK_TRIAC(TwoWire & i2c) :
  BRIICK_TRIAC(i2c, TRIAC_ADDRESS) // call the main constructor
{
  // nothing to do
}

// --------------------------------------------------

// Constructor
//  @param (i2c) : the I2C/TWI bus used for communication [TwoWire]
//  @param (address) : the I2C address of the device [uint8_t]
BRIICK_TRIAC::BRIICK_TRIAC(TwoWire & i2c, uint8_t address) :
#ifdef BRIICK_TRIAC_DEBUG
  _debugger(nullptr),
#endif
  _i2c(nullptr),
  _address(address),
  _initialized(false),
  _state(LOW)
{
  this->_i2c = &i2c;
}

// --------------------------------------------------
// --------------------------------------------------

// Configure the BRIICK
//  @param (force) : true to force the initialization [bool]
//  @returns true if successful [bool]
//  Note: the I2C/TWI bus must be initialized before configuring the object.
//  Note: the force feature shouldn't be necessary, but it might be helpful in some cases.
bool BRIICK_TRIAC::config(bool force) {
  // check if already initialized
  if (this->_initialized) {
    if (force) {
      this->_initialized = false; // reset
    } else {
      return true;
    }
  }
  
  // Note (for future reference)
  // <Wire.begin()> could be used to make sure the I2C communication is
  // configured and active, but it might be problematic if several calls
  // to <Wire.begin()> would occur in the same program, as it resets
  // the driver. Instead, the library uses a reference to the bus and
  // tries to communicate over it as master.

  // configure the GPIO
  uint8_t register_mask = ~TRIAC_DRIVER; // only the driver as output
  this->_i2c->beginTransmission(this->_address);
  this->_i2c->write(TRIAC_REGISTER_CONFIG);
  this->_i2c->write(register_mask);
  if (this->_i2c->endTransmission() == 0) {
    this->_initialized = true; // set
  } else {
#ifdef BRIICK_TRIAC_DEBUG
    if (this->_debugger != nullptr) {
      this->_debugger->println("Couldn't access the TRIAC");
    }
#endif
  }

  return this->_initialized;
}

// --------------------------------------------------

// Get the state the device
//  @returns the state (0 or 1) [uint8_t]
//  Note: this returns the internal state, not the real one.
uint8_t BRIICK_TRIAC::getState(void) {
  return this->_state;
}

// --------------------------------------------------

// Turn off the device
//  @returns true if successful [bool]
bool BRIICK_TRIAC::off(void) {
  return this->_setState(LOW);
}

// --------------------------------------------------

// Turn on the device
//  @returns true if successful [bool]
bool BRIICK_TRIAC::on(void) {
  return this->_setState(HIGH);
}

// --------------------------------------------------

// Set the debugger of the object
//  @param (stream) : the stream to print to [Stream &]
#ifdef BRIICK_TRIAC_DEBUG
void BRIICK_TRIAC::setDebugger(Stream & stream) {
  this->_debugger = &stream;
}
#endif // BRIICK_TRIAC_DEBUG

// --------------------------------------------------

// Set the state of the device (on/off)
//  @param (level) : the level to set (0 or 1) [uint8_t]
//  @returns true if successful [bool]
bool BRIICK_TRIAC::_setState(uint8_t level) {
  // check if initialized
  if (!this->_initialized) {
    return false;
  }

  uint8_t state_mask = (level == HIGH) ? TRIAC_DRIVER : 0x00;

  // send the data
  this->_i2c->beginTransmission(this->_address);
  this->_i2c->write(TRIAC_REGISTER_OUTPUT); // "bit values in this register - TRIAC_REGISTER_OUTPUT - have no effect on pins defined as inputs"
  this->_i2c->write(state_mask);
  if (this->_i2c->endTransmission() == 0) {
    this->_state = (level == HIGH) ? HIGH : LOW; // update
    return true;
  } else {
#ifdef BRIICK_TRIAC_DEBUG
    if (this->_debugger != nullptr) {
      this->_debugger->println("Couldn't write to the TRIAC");
    }
#endif
  }

  return false;
}

// --------------------------------------------------
