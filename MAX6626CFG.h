/*
    @file      MAX6266CFG.h
    @author    Sandeepan Sengupta, Tamojit Saha
    @website  https://www.sandeepan.info,
              https://www.tamojitsaha.info

    @Library   https://github.com/TamojitSaha/MAX6626
    @license   CC-BY-SA 4.0

    I2C Driver for Maxim's MAX6626 12Bit Temperature Sensor
    Version 1.0.1 -First Patch for v1.0
*/
#ifndef _MAX6626CFG_H_
#define _MAX6626CFG_H_

typedef enum
{
  ADDR_VCC = 0x48,
  ADDR_GND = 0x49,
  ADDR_SCL = 0x4A,
  ADDR_SDA = 0x4B
} address;

typedef enum
{
  f1 = 0, //0xE7
  f2 = 1, //0x08
  f3 = 2, //0x10
  f4 = 3, //0x18
  F1 = 0, //0xE7
  F2 = 1, //0x08
  F3 = 2, //0x10
  F4 = 3 //0x18
} depth;

#endif
