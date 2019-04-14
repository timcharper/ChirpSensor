#include <Wire.h>
#include <Arduino.h>

#ifndef Chirp_h
#define Chirp_h

class ChirpSensor {
private:
  char addr;
public:
  /**
   * addr is the address of the sensor; by default, this is 0x20
   *
   * Using an AVR programmer, address 0x01 of Chirp's eeprom can be changed to set the address. You can also use the API
   * call.
   *
   */
  ChirpSensor(char addr = 0x20);
  /**
   * You must call begin after Wire.begin(), and within 9 seconds of the sensor starting up; otherwise the sensor will
   * go in to autonomous mode and not respond to I2C requests.
   */
  void begin();
  void triggerLightReading();
  char getAddr();
  unsigned int readLight();
  unsigned int readMoisture();

  /**
   * The sensor can sometimes accumulate extra values and get out of sync
   */
  void flush();
};

#endif
