#include <Servo.h>

Servo myservo;  // Create servo object to control a servo

int servoPin = 9;  // Pin where the servo is connected
int pos = 90;      // Neutral position for stopping the servo
int direction = 1; // Variable to change direction
unsigned long previousMillis = 0;
unsigned long interval = 20; // Milliseconds for servo updates

void setup() {
  myservo.attach(servoPin);  // Attach the servo on pin 9
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    pos += direction;
    myservo.write(pos);
    Serial.println(pos);

    if (pos >= 180 || pos <= 90) {
      direction = -direction;
      delay(2000);
    }
  }

  // Here we don't need to use delay(), so the code runs non-blocking
}
