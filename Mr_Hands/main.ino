#include <Servo.h>

// Define pin assignments
const int emgPin = A0;      // Analog pin for EMG sensor
const int servo1Pin = 9;    // Digital pin for first servo
const int servo2Pin = 10;   // Digital pin for second servo

// Create servo objects
Servo servo1;
Servo servo2;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Attach servo objects to their respective pins
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  // Calibrate servos to their initial positions
  calibrateServos();
}

void loop() {
  // Read EMG sensor value
  int emgValue = analogRead(emgPin);

  // Map the EMG value to servo angles (adjust the range based on your sensor)
  int angle1 = map(emgValue, 0, 1023, 0, 180);
  int angle2 = map(emgValue, 0, 1023, 180, 0);

  // Control the servo motors
  moveServos(angle1, angle2);

  // Print EMG value and servo angles to serial monitor
  printData(emgValue, angle1, angle2);

  delay(50);  // Adjust the delay based on your application
}

void calibrateServos() {
  // Move servos to initial positions for calibration
  servo1.write(90);
  servo2.write(90);

  delay(1000);  // Allow time for servos to reach their positions
}

void moveServos(int angle1, int angle2) {
  // Move the servo motors to the specified angles
  servo1.write(angle1);
  servo2.write(angle2);
}

void printData(int emgValue, int angle1, int angle2) {
  // Print EMG value and servo angles to serial monitor
  Serial.print("EMG Value: ");
  Serial.print(emgValue);
  Serial.print("\tServo 1 Angle: ");
  Serial.print(angle1);
  Serial.print("\tServo 2 Angle: ");
  Serial.println(angle2);
}