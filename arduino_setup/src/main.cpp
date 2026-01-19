#include <Arduino.h>
#include "telemetry.h"

void setup() {
  Serial.begin(115200);
  telemetryInit();
}

void loop() {
  telemetryUpdate();
}
