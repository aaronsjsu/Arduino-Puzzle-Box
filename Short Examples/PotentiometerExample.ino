// Example for how to use potentiometers with an arduino.

// Asign potentiometer pins.
const int potPin1 = A3, potPin2 = A4, potPin3 = A5;

// Create variables for potentiometer values (between 0 and 1023).
int potValue1;
int potValue2;
int potValue3;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read the potentiometer values.
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);
  
  // Print potentiometer values.
  Serial.print("1: " + String(potValue1));
  Serial.print("  2: " + String(potValue2));
  Serial.println("  3: " + String(potValue3));
  delay(500);
}

