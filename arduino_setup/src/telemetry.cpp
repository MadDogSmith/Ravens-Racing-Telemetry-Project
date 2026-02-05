#include <Arduino.h>
#include "telemetry.h"

// ===================== CONFIG =====================
#define BAUD_RATE 9600
#define SAMPLE_RATE_MS 100     // 10 Hz
#define RECORD_TIME_SEC 10     // store last 10 seconds
#define MAX_SAMPLES (RECORD_TIME_SEC * 1000 / SAMPLE_RATE_MS)

// ===================== ENUM KEYS =====================
typedef enum {
  KEY_SPEED,
  KEY_THROTTLE,
  KEY_RPM
} TelemetryKey;

// ===================== TELEMETRY STRUCT =====================
typedef struct {
  float speed;
  float throttle;
  int rpm;
  unsigned long timestamp;
} Telemetry;

// ===================== STORAGE =====================
Telemetry buffer[MAX_SAMPLES];
int head = 0;          // next write position
int count = 0;         // how many valid samples stored

unsigned long lastSampleTime = 0;

// ===================== SETUP =====================
void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) {;}
  Serial.println("READY");
}

// ===================== HELPERS =====================
void storeTelemetry(float speed, float throttle, int rpm) {
  buffer[head].speed = speed;
  buffer[head].throttle = throttle;
  buffer[head].rpm = rpm;
  buffer[head].timestamp = millis();

  head = (head + 1) % MAX_SAMPLES;
  if (count < MAX_SAMPLES) count++;
}

float getValue(int index, TelemetryKey key) {
  switch (key) {
    case KEY_SPEED: return buffer[index].speed;
    case KEY_THROTTLE: return buffer[index].throttle;
    case KEY_RPM: return buffer[index].rpm;
    default: return 0;
  }
}

void dumpBuffer() {
  Serial.println("DUMP_BEGIN");

  for (int i = 0; i < count; i++) {
    int idx = (head - count + i + MAX_SAMPLES) % MAX_SAMPLES;

    Serial.print("T=");
    Serial.print(buffer[idx].timestamp);
    Serial.print(",SPEED=");
    Serial.print(buffer[idx].speed, 1);
    Serial.print(",THROTTLE=");
    Serial.print(buffer[idx].throttle, 2);
    Serial.print(",RPM=");
    Serial.println(buffer[idx].rpm);
  }

  Serial.println("DUMP_END");
}

// ===================== LOOP =====================
void loop() {
  unsigned long now = millis();

  // ----- Sampling -----
  if (now - lastSampleTime >= SAMPLE_RATE_MS) {
    lastSampleTime = now;

    float speed = random(0, 400) / 10.0;
    float throttle = random(0, 100) / 100.0;
    int rpm = random(1000, 8000);

    storeTelemetry(speed, throttle, rpm);

    // live stream
    Serial.print("LIVE,SPEED=");
    Serial.print(speed, 1);
    Serial.print(",THROTTLE=");
    Serial.print(throttle, 2);
    Serial.print(",RPM=");
    Serial.println(rpm);
  }

  // ----- Serial Commands -----
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "DUMP") {
      dumpBuffer();
    }
  }
}
