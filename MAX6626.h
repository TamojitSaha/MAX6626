/*
    @file      MAX6266.h
    @author    Sandeepan Sengupta, Tamojit Saha
    @website  https://www.sandeepan.info,
              https://www.tamojitsaha.info

    @Library   https://github.com/TamojitSaha/MAX6626
    @license   CC-BY-SA 4.0


    I2C Driver for Maxim's MAX6626 12Bit Temperature Sensor
    Version 1.0.1 -First Patch for v1.0
*/

#ifndef _MAX6626_H_
#define _MAX6626_H_
#include "MAX6626CFG.h"


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Wire.h"

/*
  #define ADDR_GND              0x48
  #define ADDR_VCC              0x49
  #define ADDR_SDA              0x4A
  #define ADDR_SCL              0x4B
*/

#define TEMP_REG              0x00
#define CONF_REG              0x01
#define T_LOW_REG             0x02
#define T_HIGH_REG            0x03

#define CONF_REG_SHUTDOWN     0x01
#define CONF_REG_COMP_INT     0x02      //Compare Mode or Interrupt Mode
#define CONF_REG_OT_POLARITY  0x04

#define FAULT_DEPTH_1         0x08
#define FAULT_DEPTH_2         0x10
#define FAULT_DEPTH_3         0x18
#define FQ_BITS_CLEAR_MASK    0xE7

class MAX6626
{
  public:
    MAX6626();
    boolean begin(address addr = ADDR_GND); //Default to ADDR_GND
    float readTemp(void);
    void sleep(void);
    void wake(void);
    void setWakeDelay(uint32_t);
    void setInterruptMode(bool flag);
    void setOTpolarity(bool flag);
    void setFaultQueueDepth(uint8_t depth);
    void setTHigh(int8_t t_high);
    void setTLow(int8_t t_low);
    float readTHigh(void);
    float readTLow(void);
    uint8_t readConfig(void);

  private:
    uint32_t wakeDelay = 250;	//Default
    uint8_t i2caddr;
    uint8_t conf_register;
    void shutdown_wake(uint8_t sw);
    void write8(uint8_t reg, uint8_t val);
    void write16(uint8_t reg, uint16_t val);
    uint16_t read16(uint8_t reg);
    float rawToTemperature(uint16_t rawValue);
    uint16_t temperatureToRaw(int8_t temp);
};
#endif
