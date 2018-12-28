/*
    @file      MAX6266.ino
    @author    Tamojit Saha
    @website   www.tamojitsaha.info

    @license   CC-BY-SA 4.0(See license.txt)

    This is a demo sketch for interfacing with MAX6266

    This sketch assumes that ADDR pin is conncted to GND.

    UPDATE: 
    21 Dec 2018
      - Added support for ATtiny 85 and ATtiny 45 but not tested.
*/

#if defined(__AVR_ATtiny85__) || defined (__AVR_ATtiny45__)
#define __NO_DEBUG__
#else
#define __DEBUG__
#endif

#include "MAX6626.h"

//Create MAX6626 Temperature Sensor Object
MAX6626 tempSensor = MAX6626();

void setup()
{
#ifdef __DEBUG__
  Serial.begin(9600);
#endif
  //tempSensor.begin(ADDR_VCC)
  //tempSensor.begin(ADDR_SCL)
  //tempSensor.begin(ADDR_SDA)
  if (!tempSensor.begin())    //Default: tempSensor.begin(ADDR_GND)
  {
#ifdef __DEBUG__
    Serial.println("MAX6626 not found!");
#endif
    while (1);
  }
}

void loop()
{
  /*Wake up MAX6626*/
  //Serial.println("Wake up MAX6626");
  //tempSensor.wake();

  //Read and print the temperature
  float c = tempSensor.readTemp();          //returns value in deg C
  float f = c * 9.0 / 5.0 + 32;             //convert deg C to deg F
#ifdef __DEBUG__
  Serial.print("Temp: "); Serial.print(c, 4); //print 4 point decimal value
  Serial.print("*C\t"); Serial.print(f, 4);
  Serial.println("*F");
#endif
  //Serial.println("Shutdown MAX6626");
  //tempSensor.sleep();

  delay(2000);
}
