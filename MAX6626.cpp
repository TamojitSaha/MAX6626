/*
    @file      MAX6266.cpp
    @author    Sandeepan Sengupta, Tamojit Saha
    @website   http://www.tamojitsaha.info

    @license   CC-BY-SA 4.0(See license.txt)

    I2C Driver for Maxim's MAX6626 12Bit Temperature Sensor
    Version 1.0.1 -First Patch for v1.0
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if defined (__AVR_ATtiny85__) ||defined (__AVR_ATtiny45__)
#include "TinyWireM.h"
#else
#include <Wire.h>
#endif

#include "MAX6626.h"

MAX6626::MAX6626() {
}

boolean MAX6626::begin(address addr)
{
  Wire.begin();
  i2caddr = addr;
  conf_register = readConfig();

  Wire.beginTransmission(i2caddr);
  uint8_t err = Wire.endTransmission();
  if (err != 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

float MAX6626::readTemp(void)
{
  uint16_t _temp = read16(TEMP_REG);
  float temperature = rawToTemperature(_temp);
  /*if (round(temperature) < -124.0 || round(temperature) > 124.0)
    {
    shutdown();
    return 0;
    }*/
  return temperature;
}

void MAX6626::sleep() {
  shutdown_wake(1);
}

void MAX6626::wake() {
  shutdown_wake(false);
  delay(wakeDelay);
}

void MAX6626::setWakeDelay(uint32_t wkDelay) {
	wakeDelay = wkDelay;
}

void MAX6626::setInterruptMode(bool sw)
{
  volatile uint8_t reg = (uint8_t)readConfig();
  if (sw == true)
  {
    reg |= CONF_REG_COMP_INT;
    conf_register = reg;
    write8(CONF_REG, conf_register);
  }
  if (sw == false)
  {
    reg &= ~CONF_REG_COMP_INT;
    conf_register = reg;
    write8(CONF_REG, conf_register);
  }
}

void MAX6626::setOTpolarity(bool sw)
{
  volatile uint8_t reg = (uint8_t)readConfig();
  if (sw == true)
  {
    reg |= CONF_REG_OT_POLARITY;
    conf_register = reg;
    write8(CONF_REG, conf_register);
  }
  if (sw == false)
  {
    reg &= ~CONF_REG_OT_POLARITY;
    conf_register = reg;
    write8(CONF_REG, conf_register);
  }
}

void MAX6626::setFaultQueueDepth(uint8_t depth)
{
  volatile uint8_t  reg = (uint8_t)readConfig();
  if (depth < 0) depth = 0;
  if (depth > 3) depth = 3;
  if (depth >= 0 && depth <= 3)
  {
    switch (depth)
    {
      case 0:
        reg &= FQ_BITS_CLEAR_MASK;
        conf_register = reg;

        write8(CONF_REG, conf_register);
        break;

      case 1:
        reg &= FQ_BITS_CLEAR_MASK;
        reg |= FAULT_DEPTH_1;
        conf_register = reg;
        write8(CONF_REG, conf_register);
        break;

      case 2:
        reg &= FQ_BITS_CLEAR_MASK;
        reg |= FAULT_DEPTH_2;
        conf_register = reg;
        write8(CONF_REG, conf_register);
        break;

      case 3:
        reg &= FQ_BITS_CLEAR_MASK;
        reg |= FAULT_DEPTH_3;
        conf_register = reg;
        write8(CONF_REG, conf_register);
        break;
    }
  }
}

void MAX6626::setTHigh(int8_t t_high)
{
  write16(T_HIGH_REG, temperatureToRaw(t_high));
}

void MAX6626::setTLow(int8_t t_low)
{
  write16(T_LOW_REG, temperatureToRaw(t_low));
}

uint8_t MAX6626::readConfig()
{
  Wire.beginTransmission(i2caddr);
  Wire.write(CONF_REG);
  Wire.endTransmission();
  Wire.requestFrom(i2caddr, 1);
  uint8_t config_reg = Wire.read();
  Wire.endTransmission();

  return config_reg;
}

float MAX6626::readTHigh()
{
  uint16_t _th = read16(T_HIGH_REG);
  float t_high = rawToTemperature(_th);

  return t_high;
}


float MAX6626::readTLow()
{
  uint16_t _tl = read16(T_LOW_REG);
  float t_low = rawToTemperature(_tl);

  return t_low;
}


void MAX6626::shutdown_wake(uint8_t sw)
{
  uint8_t conf_shutdown ;
  if (sw == 1)
  {
    conf_shutdown = conf_register |  CONF_REG_SHUTDOWN;
    write8(CONF_REG, conf_shutdown);
  }
  if (sw == 0)
  {
    conf_shutdown = conf_register &  ~CONF_REG_SHUTDOWN;
    write8(CONF_REG, conf_shutdown);
  }
}


uint16_t MAX6626::read16(uint8_t reg)
{
  uint16_t val;
  Wire.beginTransmission(i2caddr);
  Wire.write(uint8_t(reg));
  Wire.endTransmission();
  Wire.requestFrom(i2caddr, uint8_t(2));
  val = Wire.read();
  val <<= 8;
  val |= Wire.read();
  Wire.endTransmission();
  return val;
}

void MAX6626::write16(uint8_t reg, uint16_t val)
{
  Wire.beginTransmission(i2caddr);
  Wire.write(uint8_t(reg));
  Wire.write(val >> 8);
  Wire.write(val & 0xff);
  Wire.endTransmission();
}

void MAX6626:: write8(uint8_t reg, uint8_t val)
{
  Wire.beginTransmission(i2caddr);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

float MAX6626:: rawToTemperature(uint16_t rawValue)
{
  float actual_temperature = rawValue / 256.0 ;
  if (rawValue & 0x8000)
  {
    actual_temperature -= 256.0;
  }
  return actual_temperature;
}


uint16_t MAX6626:: temperatureToRaw(int8_t temp)
{
  uint16_t val;

  if (temp < 0)
  {
    if (temp < -125)
    {
      temp = -125;
    }
    val = temp + 256;
  }
  else {
    if (temp > 125)
    {
      temp = 125;
    }
    val = temp;
  }
  val <<= 8;
  return val;
}
