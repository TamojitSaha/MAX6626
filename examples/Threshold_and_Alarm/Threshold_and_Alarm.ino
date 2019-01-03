/*
    @file      MAX6266.ino
    @author    Tamojit Saha
    @website   https://www.tamojitsaha.info
    
    @Library   https://github.com/TamojitSaha/MAX6626_library
    @license   CC-BY-SA 4.0(See license.txt)

    This sketch demonstrates how temperature thresholds
    can be defined. THigh and TLow are 8 bit regiters
    The functions accepts Celsius degree format temperature

    Range: -125 deg C to 125 deg C

     - setTHigh(25)  --> Sets temperature threshold to 25 C
     - setTLow(-10)  --> Sets temperature threshold to -10 C

    The OT pin is active low unless defined.
    So, by default, it asserts LOW logic when T_HIGH is reached and will
    deassert only when T_LOW is reached.

    Setting OT pin polarity:
     - setOTpolarity(true) --> Sets the OT pin polarity to Active High.

   Setting Fault Queue Depth:
   This sets the number of consecutive out-of-tolerance temperature
   readings that must occur before the OT alarm output is toggled.
   The fault queue clears up at power-up, in shutdown, or if a master 
   writes to any of the T_HIGH , T_LOW or configuration registers.
     +-------+---------------+
     | Depth | No. of Faults |
     +-------+---------------+
     |     0 | 1(default)    |
     |     1 | 2             |
     |     2 | 4             |
     |     3 | 6             |
     +-------+---------------+     * 
   
   This sketch assumes that ADDR pin is conncted to GND.
*/
#if defined(__AVR_ATtiny85__) || defined (__AVR_ATtiny45__)
#define __NO_DEBUG__
#else
#define __DEBUG__
#endif

#include <MAX6626.h>

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
  // Setting the temperature thresholds
  setTempThresholds(25, 22);

  //Setting Fault Queue Depth to 6
  tempSensor.setFaultQueueDepth(3);
}


void loop() {
  //Read and print the temperature
  float c = tempSensor.readTemp();          //returns value in deg C
  float f = c * 9.0 / 5.0 + 32;             //convert deg C to deg F
#ifdef __DEBUG__
  Serial.print("Temp: "); Serial.print(c, 4); //print 4 point decimal value
  Serial.print("*C\t"); Serial.print(f, 4);
  Serial.println("*F");
  Serial.println();

  //Reading Configuration register bits
  Serial.print("Configuration Register: ");
  Serial.println(tempSensor.readConfig(), BIN);
#endif
  delay(250);
}

void setTempThresholds(int8_t highTemp, int8_t lowTemp)
{
  tempSensor.setTHigh(highTemp);
  tempSensor.setTLow(lowTemp);
}
