#include <Arduino.h>
#include "telemetry.h"

void setup() {
  Serial.begin(9600);
  telemetryInit();
}

void loop() {
  telemetryUpdate();
}
