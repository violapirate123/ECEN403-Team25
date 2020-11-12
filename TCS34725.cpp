#ifdef __AVR
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#endif
#include <math.h>
#include <stdlib.h>

#include "TCS34725.h"

// Power function
float powf(const float x, const float y) 
{
  return (float)(pow((double)x, (double)y));
}

// Writes a register and an 8 bit value over I2C
void TCS34725::write8(uint8_t reg, uint32_t value) 
{
  _wire->beginTransmission(_i2caddr);
#if ARDUINO >= 100
  _wire->write(TCS34725_COMMAND_BIT | reg);
  _wire->write(value & 0xFF);
#else
  _wire->send(TCS34725_COMMAND_BIT | reg);
  _wire->send(value & 0xFF);
#endif
  _wire->endTransmission();
}

// Reads an 8 bit value over I2C
uint8_t TCS34725::read8(uint8_t reg) 
{
  _wire->beginTransmission(_i2caddr);
  #if ARDUINO >= 100
    _wire->write(TCS34725_COMMAND_BIT | reg);
  #else
    _wire->send(TCS34725_COMMAND_BIT | reg);
  #endif
    _wire->endTransmission();

  _wire->requestFrom(_i2caddr, (uint8_t)1);
  #if ARDUINO >= 100
    return _wire->read();
  #else
    return _wire->receive();
  #endif
}

// Reads a 16 bit values over I2C
uint16_t TCS34725::read16(uint8_t reg) 
{
  uint16_t x;
  uint16_t t;

  _wire->beginTransmission(_i2caddr);
  #if ARDUINO >= 100
    _wire->write(TCS34725_COMMAND_BIT | reg);
  #else
    _wire->send(TCS34725_COMMAND_BIT | reg);
  #endif
    _wire->endTransmission();

  _wire->requestFrom(_i2caddr, (uint8_t)2);
  #if ARDUINO >= 100
    t = _wire->read();
    x = _wire->read();
  #else
    t = _wire->receive();
    x = _wire->receive();
  #endif
    x <<= 8;
    x |= t;
    return x;
}

// Enables the device
void TCS34725::enable() 
{
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
  delay(3);
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
  delay(700);
}

// Disables the device (lower power sleep mode)
void TCS34725::disable() 
{
  // Turn the device off to save power
  uint8_t reg = 0;
  reg = read8(TCS34725_ENABLE);
  write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

/*!
 *  @brief  Constructor
 *  @param  it
 *          Integration Time
 *  @param  gain
 *          Gain
 */
TCS34725::TCS34725(tcs34725IntegrationTime_t it,tcs34725Gain_t gain) 
{
  _tcs34725Initialised = false;
  _tcs34725IntegrationTime = it;
  _tcs34725Gain = gain;
}

// Initializes I2C and configures the sensor
boolean TCS34725::begin(uint8_t addr) 
{
  _i2caddr = addr;
  _wire = &Wire;
  return init();
}

// Initializes I2C and configures the sensor
boolean TCS34725::begin(uint8_t addr, TwoWire *theWire) 
{
  _i2caddr = addr;
  _wire = theWire;
  return init();
}

// Initializes I2C and configures the sensor
boolean TCS34725::begin() 
{
  _i2caddr = TCS34725_ADDRESS;
  _wire = &Wire;
  return init();
}

// Initialization
boolean TCS34725::init() 
{
  _wire->begin();
  // Make sure we're actually connected
  uint8_t x = read8(TCS34725_ID);
  if ((x != 0x44) && (x != 0x10)) 
  {
    return false;
  }
  _tcs34725Initialised = true;
  // Note: by default, the device is in power down mode on bootup
  enable();
  return true;
}

// Reads the raw red, green, blue and clear channel values
void TCS34725::getRawData(uint16_t *r, uint16_t *g, uint16_t *b) 
{
  if (!_tcs34725Initialised)
    begin();
  *r = read16(TCS34725_RDATAL);
  *g = read16(TCS34725_GDATAL);
  *b = read16(TCS34725_BDATAL);
  delay(700);
}
