/*
    @file      MAX6266.ino
    @author    Tamojit Saha
    @website   www.tamojitsaha.info

    @license   CC-BY-SA 4.0(See license.txt)

    This is a demo sketch for interfacing with MAX6266

    This sketch assumes that ADDR pin is conncted to GND.
*/

#include "MAX6626.h"

//Create MAX6626 Temperature Sensor Object
MAX6626 tempSensor = MAX6626();

void setup()
{
  Serial.begin(9600);
  //tempSensor.begin(ADDR_VCC)
  //tempSensor.begin(ADDR_SCL)
  //tempSensor.begin(ADDR_SDA)
  if (!tempSensor.begin())    //Default: tempSensor.begin(ADDR_GND)
  {
    Serial.println("MAX6626 not found!");
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
  Serial.print("Temp: ");Serial.print(c,4); //print 4 point decimal value
  Serial.print("*C\t");Serial.print(f,4);
  Serial.println("*F");

  //Serial.println("Shutdown MAX6626");
  //tempSensor.sleep();

  delay(2000);
}
