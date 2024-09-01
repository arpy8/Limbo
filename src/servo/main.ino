#include <Servo.h>

#define INDEX 3
#define MIDDLE 4
#define RING 5
#define PINKY 6
#define THUMB 7


Servo index;  // create servo object to control a servo
Servo middle;  // create servo object to control a servo
Servo ring;  // create servo object to control a servo
Servo pinky;  // create servo object to control a servo
Servo thumb;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  index.attach(INDEX);
  middle.attach(MIDDLE);
  ring.attach(RING);
  pinky.attach(PINKY);
  thumb.attach(THUMB);
}

void loop() {
  check_all_fingers();
  delay(1500);

  move_all_fingers_simultaneously();
  delay(1500);
  
  do_yo_yo();
  delay(1500);
}

void pull_finger(Servo finger) {
  close_finger(finger);
  delay(500);
  open_finger(finger);
  delay(500);
}

void check_all_fingers(){
  Servo fingers[5] = {index, middle, ring, pinky, thumb};
  
  for (int i = 0; i < 5; i++) {
    pull_finger(fingers[i]);
  }
}

void do_yo_yo() {
  Servo fingers[3] = {middle, ring, thumb};
  move_specific_fingers_simultaneously(fingers, 3);
}

void move_all_fingers(int position) {
  index.write(position);
  middle.write(position);
  ring.write(position);
  pinky.write(position);
  thumb.write(position);
}

void move_specific_fingers(int position, Servo fingers[], int size) {
  for(int i=0;i<size;i++)
  {
    fingers[i].write(position);
  }
}

void move_specific_fingers_simultaneously(Servo fingers[], int size) {
  for (int pos = 0; pos <= 90; pos += 1) {
    move_specific_fingers(pos, fingers, size);
    delay(15);
  }
  
  for (int pos = 90; pos >= 0; pos -= 1) {
    move_specific_fingers(pos, fingers, size);
    delay(15);
  }
}

void move_all_fingers_simultaneously() {
  for (int pos = 0; pos <= 90; pos += 1) {
    move_all_fingers(pos);
    delay(15);
  }
  
  for (int pos = 90; pos >= 0; pos -= 1) {
    move_all_fingers(pos);
    delay(15);
  }
}

void close_finger(Servo finger) {
  finger.write(0);
}

void open_finger(Servo finger) {
  finger.write(90);
}