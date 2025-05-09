#include <Servo.h>

const int greenLedPin = 13;
const int blueLedPin = 12;
const int ldrPin = A0;
const int tempPin = A1;
const int servoPin = 11;

Servo servoMotor;

int currentAngle = 90;

void setup() {
  Serial.begin(9600);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  servoMotor.attach(servoPin);

  servoMotor.write(currentAngle);
  delay(1000);
}

void loop() {
  int tempReading = analogRead(tempPin);
  float voltage = tempReading * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  int targetAngle;
  if (temperature < 25) {
    targetAngle = 0;
  } else {
    targetAngle = 180;
  } 
  
  if (currentAngle < targetAngle) {
    currentAngle = min(targetAngle, currentAngle++);
  } else if (currentAngle > targetAngle) {
    currentAngle = max(targetAngle, currentAngle--);
  }
  
  servoMotor.write(currentAngle);
  
  int lightLevel = analogRead(ldrPin);
  if (lightLevel < 500) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(blueLedPin, LOW);
  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(blueLedPin, HIGH);
  }
  
  Serial.print("Temperatuur: ");
  Serial.print(temperature);
  Serial.print(" °C, Valgustugevus: ");
  Serial.println(lightLevel);
  
  delay(10);
}
