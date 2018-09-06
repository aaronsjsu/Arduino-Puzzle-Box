// This code was written for an arduino puzzle box. The circuit includes an lcd display, 3 potentiometers, 
// 3 latching buttons, and a servo. The lcd display gives feedback to the user. There are 3 puzzles to be
// solved before the box will be opened. Each puzzle is solved by moving the potentiometer values to a 
// certain position (on the box there are symbols to represent the range), and pushing certain buttons.
// The user must find the solutions elsewhere. After each puzzle is solved, the box will unlock. 


#include <LiquidCrystal.h> // Library for lcd display
#include <Servo.h> // Library for servo

// Lcd display pins
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;

// Potentiometer pins (analog)
const int potPin1 = 3, potPin2 = 4, potPin3 = 5;

// Button pins
const int buttonPin1 = 7, buttonPin2 = 5, buttonPin3 = 3;
const int buttonLedPin1 = 6, buttonLedPin2 = 4, buttonLedPin3 = 2;

// Servo pin
const int servoPin = 0;

// Potentiometer resistance/location values (between 0 and 1023)
int potValue1;
int potValue2;
int potValue3;

// Potentiometer zones (beginning of each zone), 4 zones in total
const int potZone1 = 100;
const int potZone2 = 470;
const int potZone3 = 810;
const int potZone4 = 0;

// Button states
int buttonState1;
int buttonState2;
int buttonState3;
// Button states for the previous loop, used to detect when the button state changes
int prevButtonState1;
int prevButtonState2;
int prevButtonState3;

// Servo angles (has to be value between 0 and 180)
int servoAngleOpen = 50;
int servoAngleClosed = 130;

// Keeps track of when the puzzle is solved
bool puzzleSolved = false;

// Keeps track of the first time through loop()
bool firstLoop = true;

// Keep track of when each of our three challenges are done
bool solvedChallenge1 = false;
bool solvedChallenge2 = false;
bool solvedChallenge3 = false;

// Initialize the display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Create servo object
Servo servo;

void setup() {
  // Attach the servo
  servo.attach(servoPin);
  servo.write(servoAngleClosed);
  
  // Set up the LCD's columns and rows
  lcd.begin(16, 2);
  
  // Attach the buttons and their led's
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonLedPin1, OUTPUT);
  pinMode(buttonLedPin2, OUTPUT);
  pinMode(buttonLedPin3, OUTPUT);

  // Make sure all button led's are off
  digitalWrite(buttonLedPin1, LOW);
  digitalWrite(buttonLedPin2, LOW);
  digitalWrite(buttonLedPin3, LOW);

  //Serial.begin(9600);
  lcd.clear();
  lcd.print("Hello There!");
  
}

void checkIfChallenge1Solved() {
  Serial.println("Checking challenge 1");
  if (potValue1 < potZone2 && potValue1 > potZone1 && // If potentiometer 1 is in zone 1
      potValue2 < potZone1 &&                         // If potentiometer 2 is in zone 4
      potValue3 < potZone3 && potValue3 > potZone2 && // If potentiometer 3 is in zone 2
      buttonState1 == HIGH &&                         // If button1 pressed
      buttonState2 == LOW  &&                         // If button2 unpressed
      buttonState3 == HIGH) {                         // If button3 pressed
    solvedChallenge1 = true;
    lcd.clear();
    //Play riddle
    lcd.print("You solved the");
    lcd.setCursor(0, 1);
    lcd.print("first challenge");
  }
}

void checkIfChallenge2Solved() {
  Serial.println("Checking challenge 2");
  if (potValue1 > potZone3 &&                         // If potentiometer 1 is in zone 3
      potValue2 < potZone2 && potValue2 > potZone1 && // If potentiometer 2 is in zone 1
      potValue3 < potZone1 &&                         // If potentiometer 3 is in zone 4
      buttonState1 == LOW &&                          // If button1 unpressed
      buttonState2 == LOW  &&                         // If button2 unpressed
      buttonState3 == HIGH) {                         // If button3 pressed
    solvedChallenge2 = true;
    lcd.clear();
    //Play riddle
    lcd.print("You solved the");
    lcd.setCursor(0, 1);
    lcd.print("second challenge");
  }
}

void checkIfChallenge3Solved() {
  Serial.println("Checking challenge 3");
  if (potValue1 < potZone3 && potValue1 > potZone2 && // If potentiometer 1 is in zone 2
      potValue2 < potZone2 && potValue2 > potZone1 && // If potentiometer 2 is in zone 1
      potValue3 < potZone2 && potValue3 > potZone1 && // If potentiometer 3 is in zone 1
      buttonState1 == HIGH &&                         // If button1 pressed
      buttonState2 == HIGH  &&                        // If button2 pressed
      buttonState3 == LOW) {                          // If button3 unpressed
    solvedChallenge3 = true;
    lcd.clear();
    lcd.print("You solved the");
    lcd.setCursor(0, 1);
    lcd.print("last challenge");
    delay(3000);
    lcd.clear();
    lcd.print("Unlocking...");
    puzzleSolved = true;
  }
}

void loop() {
  delay(2000);
  servo.write(servoAngleOpen);
  delay(4000);
  servo.write(servoAngleClosed);

  // Display special messages if first loop
  if (firstLoop) {
    delay(5000);
    lcd.clear();
    lcd.print("Turn my knobs");
    lcd.setCursor(0, 1);
    lcd.print("Push my buttons");
    delay(5000);
    lcd.clear();
    lcd.print("Solve my riddles");
    lcd.setCursor(0, 1);
    lcd.print("Light my lights");
    delay(5000);
    lcd.clear();
    lcd.print("When you're done");
    lcd.setCursor(0, 1);
    lcd.print("You have won");
    delay(5000);
    lcd.clear();
    lcd.print("Good Luck!");
    firstLoop = false;
  }

  // Read potentiometer values
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);
  //Serial.print("1: " + String(potValue1));
  //Serial.print("  2: " + String(potValue2));
  //Serial.println("  3: " + String(potValue3));
  
  // Read button states (low is pushed, high is unpushed)
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);

  // Check the status of each of the three challeges
  if (solvedChallenge3) {
    digitalWrite(buttonLedPin3, HIGH);
    puzzleSolved = true;
  } else if (solvedChallenge2) {
    digitalWrite(buttonLedPin2, HIGH);
    checkIfChallenge3Solved();
  } else if (solvedChallenge1) {
    digitalWrite(buttonLedPin1, HIGH);
    checkIfChallenge2Solved();
  } else {
    checkIfChallenge1Solved();
  }

  if (puzzleSolved) {
    servo.write(servoAngleOpen);
  }
  
  delay(200);
}
