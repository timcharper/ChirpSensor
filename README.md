# ChirpSensor

This is an Arduino library for reading values from a [Chirp Watering Alarm](https://wemakethings.net/chirp/) over I2C.

It defaults to I2C address `0x20`.

## Example

```
#include <Wire.h>
#include "ChirpSensor.h"

ChirpSensor sensor(0x20);

struct ChirpReading {
  unsigned int moisture;
  unsigned int light;
};

void setup() {
  Wire.begin();
  Serial.begin(9600);

  sensor.begin();
}

void loop() {
  // reading the light value takes a while
  sensor.triggerLightReading();
  delay(5000);

  int light = sensor.readLight();
  int moisture = sensor.readMoisture();

  Serial.printf("%x Moisture: %d Light: %d\n", sensor.getAddr(), moisture, light);
  delay(5000);
}
```
