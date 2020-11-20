#ifndef _TCS34725_H_
#define _TCS34725_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>

#define TCS34725_ADDRESS (0x29) // I2C address
#define TCS34725_COMMAND_BIT (0x80) // Command bit
#define TCS34725_ENABLE (0x00) // Interrupt Enable register
#define TCS34725_ENABLE_AEN (0x02) //RGB Enable - Writing 1 actives the ADC, 0 disables it
#define TCS34725_ENABLE_PON (0x01) // Power on - Writing 1 activates the internal oscillator, 0 disables it
#define TCS34725_ATIME (0x01) // Integration time

#define TCS34725_CONTROL (0x0F) // Set the gain level for the sensor
#define TCS34725_ID (0x12) // 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727

#define TCS34725_RDATAL (0x16) // Red channel data low byte
#define TCS34725_GDATAL (0x18) // Green channel data low byte
#define TCS34725_BDATAL (0x1A) // Blue channel data low byte

// Integration time settings for TCS34725
typedef enum 
{
  TCS34725_INTEGRATIONTIME_2_4MS = 0xFF, // 2.4ms - 1 cycle    - Max Count: 1024
  TCS34725_INTEGRATIONTIME_700MS = 0x00  // 700ms - 256 cycles - Max Count: 65535
} 
tcs34725IntegrationTime_t;

// Gain settings for TCS34725
typedef enum 
{
  TCS34725_GAIN_1X = 0x00 //No gain
} 
tcs34725Gain_t;

class TCS34725 {
public:
  TCS34725(tcs34725IntegrationTime_t = TCS34725_INTEGRATIONTIME_2_4MS,tcs34725Gain_t = TCS34725_GAIN_1X);

  boolean begin(uint8_t addr, TwoWire *theWire);
  boolean begin(uint8_t addr);
  boolean begin();
  boolean init();

  void setIntegrationTime(tcs34725IntegrationTime_t it);
  void setGain(tcs34725Gain_t gain);
  void getRawData(uint16_t *r, uint16_t *g, uint16_t *b);

  void write8(uint8_t reg, uint32_t value);
  uint8_t read8(uint8_t reg);
  uint16_t read16(uint8_t reg);
  void enable();

private:
  TwoWire *_wire;
  uint8_t _i2caddr;
  boolean _tcs34725Initialised;
  tcs34725Gain_t _tcs34725Gain;
  tcs34725IntegrationTime_t _tcs34725IntegrationTime;
};

#endif
