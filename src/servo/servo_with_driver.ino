#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define INDEX 0  // Channel 0 on PCA9685
#define MIDDLE 1  // Channel 1 on PCA9685
#define RING 2  // Channel 2 on PCA9685
#define PINKY 3  // Channel 3 on PCA9685
#define THUMB 4  // Channel 4 on PCA9685

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo angles (assuming a 12-bit resolution of 4096)
#define SERVO_MIN  150  // Min pulse length out of 4096
#define SERVO_MAX  600  // Max pulse length out of 4096

void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz
}

void loop() {
  check_all_fingers();
  delay(1500);

  move_all_fingers_simultaneously();
  delay(1500);
  
  do_yo_yo();
  delay(1500);
}

void pull_finger(int finger) {
  close_finger(finger);
  delay(500);
  open_finger(finger);
  delay(500);
}

void check_all_fingers() {
  int fingers[5] = {INDEX, MIDDLE, RING, PINKY, THUMB};
  
  for (int i = 0; i < 5; i++) {
    pull_finger(fingers[i]);
  }
}

void do_yo_yo() {
  int fingers[3] = {MIDDLE, RING, THUMB};
  move_specific_fingers_simultaneously(fingers, 3);
}

void move_all_fingers(int position) {
  pwm.setPWM(INDEX, 0, position);
  pwm.setPWM(MIDDLE, 0, position);
  pwm.setPWM(RING, 0, position);
  pwm.setPWM(PINKY, 0, position);
  pwm.setPWM(THUMB, 0, position);
}

void move_specific_fingers(int position, int fingers[], int size) {
  for(int i = 0; i < size; i++) {
    pwm.setPWM(fingers[i], 0, position);
  }
}

void move_specific_fingers_simultaneously(int fingers[], int size) {
  for (int pos = SERVO_MIN; pos <= SERVO_MAX; pos += 1) {
    move_specific_fingers(pos, fingers, size);
    delay(15);
  }
  
  for (int pos = SERVO_MAX; pos >= SERVO_MIN; pos -= 1) {
    move_specific_fingers(pos, fingers, size);
    delay(15);
  }
}

void move_all_fingers_simultaneously() {
  for (int pos = SERVO_MIN; pos <= SERVO_MAX; pos += 1) {
    move_all_fingers(pos);
    delay(15);
  }
  
  for (int pos = SERVO_MAX; pos >= SERVO_MIN; pos -= 1) {
    move_all_fingers(pos);
    delay(15);
  }
}

void close_finger(int finger) {
  pwm.setPWM(finger, 0, SERVO_MIN);
}

void open_finger(int finger) {
  pwm.setPWM(finger, 0, SERVO_MAX);
}