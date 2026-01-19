#include <Arduino.h>
#include "telemetry.h"

void telemetryInit() {
  Serial.println("Telemetry ready");
}

void telemetryUpdate() {
  Serial.println("Sending data...");
  delay(1000);
}
