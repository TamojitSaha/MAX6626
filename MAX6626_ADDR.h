/*
 *  @file      MAX6266_ADDR.h
 *  @author    Sandeepan Sengupta, Tamojit Saha
 *  @website   http://www.tamojitsaha.info
 *  
 *  @license   CC-BY-SA 4.0(See license.txt) 
 *  
 *  I2C Driver for Maxim's MAX6626 12Bit Temperature Sensor
 *  Version 1.0.1 -First Patch for v1.0
 */
#ifndef _MAX6626_ADDR_H_
#define _MAX6626_ADDR_H_

typedef enum
{
  ADDR_VCC = 0x48,
  ADDR_GND = 0x49,
  ADDR_SCL = 0x4A,
  ADDR_SDA = 0x4B
}address;

#endif
