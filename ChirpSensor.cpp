#include "ChirpSensor.h"
const unsigned int NO_VALUE = 0xffff;

void writeI2CRegister8bit(char addr, unsigned char value) {
  Wire.beginTransmission(addr);
  Wire.write(value);
  Wire.endTransmission();
}

unsigned int readI2CRegister16bit(char addr, unsigned char reg) {
  writeI2CRegister8bit(addr, reg);
  int response;
  for (int i = 0; i < 10; i++) {
    delay(20);
    Wire.requestFrom(addr, 2);
    Serial.printf("Bytes available %d\n", Wire.available());
    response = Wire.read() << 8;
    response = response | Wire.read();
    if (response != NO_VALUE)
      break;
    delay(480);
  }
  return response;
}

ChirpSensor::ChirpSensor(char addr) {
  this->addr = addr;
}

void ChirpSensor::begin() {
  writeI2CRegister8bit(this->addr, 6); //reset
}

void ChirpSensor::triggerLightReading() {
  writeI2CRegister8bit(this->addr, 3);
}

unsigned int ChirpSensor::readLight() {
  this->flush();
  return readI2CRegister16bit(this->addr, 4);
}

char ChirpSensor::getAddr() {
  return this->addr;
}

unsigned int ChirpSensor::readMoisture() {
  this->flush();
  return readI2CRegister16bit(this->addr, 0);
}

/**
 * Sometimes, extra data is left in a buffer on the Chirp device, and this will cause the light and the moisture
 * readings to get mixed. Calling flush regularly ensures that any out-of-sync errors are cleared.
 */
void ChirpSensor::flush() {
  Wire.requestFrom(this->addr, 2);
  // read and discard any extraneous data
  Wire.read();
  Wire.read();
}
