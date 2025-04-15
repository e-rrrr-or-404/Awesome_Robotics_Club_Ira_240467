
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo servoA;
Servo servoB;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address might differ

const int potPin = A0;
const int buttonPin = 2;
const int servoAPin = 9;
const int servoBPin = 10;

int activeServo = 0; // 0 for A, 1 for B
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  servoA.attach(servoAPin);
  servoB.attach(servoBPin);

  pinMode(buttonPin, INPUT_PULLUP); // use internal pull-up resistor

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Servo Control");
  delay(1000);
}

void loop() {
  // Read and debounce button
  bool reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      activeServo = 1 - activeServo; // toggle between 0 and 1
    }
  }
  lastButtonState = reading;

  // Read potentiometer and map angle
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);

  // Move active servo
  if (activeServo == 0) {
    servoA.write(angle);
  } else {
    servoB.write(angle);
  }

  // Display status on LCD
  lcd.setCursor(0, 0);
  lcd.print("Servo ");
  lcd.print((activeServo == 0) ? "A" : "B");
  lcd.print(" Selected ");

  lcd.setCursor(0, 1);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print((char)223); // degree symbol
  lcd.print("     "); // clear remaining chars
  delay(100);
}
