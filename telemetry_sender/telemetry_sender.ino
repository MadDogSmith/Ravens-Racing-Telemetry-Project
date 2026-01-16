// This function runs once when the Arduino boots
void setup() {
  // Start USB serial communication at 115200 baud
  // This MUST match the baud rate used in Python
  Serial.begin(115200);

  // Some Arduino boards reset when a serial connection opens
  // This loop waits until the serial connection is ready
  while (!Serial) {
    ;
  }
}

// This function runs repeatedly after setup()
void loop() {
  // Generate simulated telemetry values
  // These stand in for real sensor data
  float speed = random(0, 400) / 10.0;      // Simulated speed: 0.0–40.0
  float throttle = random(0, 100) / 100.0;  // Simulated throttle: 0.00–1.00
  int rpm = random(1000, 8000);             // Simulated RPM: 1000–8000

  // Output a single telemetry packet
  // The format MUST stay consistent for Python parsing
  Serial.print("SPEED=");
  Serial.print(speed, 1);        // Print speed with 1 decimal place
  Serial.print(",THROTTLE=");
  Serial.print(throttle, 2);     // Print throttle with 2 decimal places
  Serial.print(",RPM=");
  Serial.println(rpm);           // println() adds the newline character

  // Control update rate (100 ms = 10 Hz)
  delay(100);
}
