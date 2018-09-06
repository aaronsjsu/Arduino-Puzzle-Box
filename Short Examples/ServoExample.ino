// Example for using a servo with arduino.

#include <Servo.h> // Include servo library.

Servo servo;  // Servo object to control a servo.

void setup() {
  servo.attach(9);  // Attaches the servo on pin 9.
}

void loop() {
  
  // write() method moves the servo to the specified angle between 0 and 180.
  servo.write(10);
  delay(2000);
  servo.write(170);
  delay(2000);
  servo.write(90);
  delay(2000);
}
