#include <Servo.h>
#include <LiquidCrystal.h>

const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 13;
const int redPin = 8;
const int greenPin = 5;
const int bluePin = 4;

const int openAngle = 90;
const int closeAngle = 0;
const int detectionDist = 15;
const long sadTimeout = 10000;

Servo servo;
LiquidCrystal lcd(6, 7, 9, 10, 11, 12);
int coinCount = 0;
unsigned long lastDetectionTime = 0;
bool lidOpen = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  servo.attach(servoPin);
  servo.write(closeAngle);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Tere tulemast!");
  lcd.setCursor(0, 1);
  lcd.print("Sastuspanka!");

  setColor(0, 0, 255);

  delay(1000);
}

void loop() {
  long distance = measureDistance();

  if (distance > 0 && distance < detectionDist) {
    handleDetection();
  } 
  else {
    if (lidOpen) {
      if (millis() - lastDetectionTime > 500) {
        closeLid();
      }
    } 
    else {
      checkSadState();
    }
  }

  updateDisplay();
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void handleDetection() {
  lastDetectionTime = millis();

  if (!lidOpen) {
    openLid();
    coinCount++;
    setColor(0, 255, 0);
    delay(1000);
  }
}

void openLid() {
  servo.write(openAngle);
  lidOpen = true;
}

void closeLid() {
  servo.write(closeAngle);
  lidOpen = false;
  setColor(0, 0, 255);
}

void checkSadState() {
  if (millis() - lastDetectionTime > sadTimeout) {
    setColor(255, 0, 0);
  }
}

void updateDisplay() {
  lcd.clear();

  if (lidOpen) {
    lcd.setCursor(0, 0);
    lcd.print("Aitah mundi eest!");
    lcd.setCursor(0, 1);
    lcd.print("Mundid: ");
    lcd.print(coinCount);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Mundid kokku: ");
    lcd.print(coinCount);

    lcd.setCursor(0, 1);
    if (millis() - lastDetectionTime > sadTimeout) {
      lcd.print("Ootan juba kaua:(");
    } else if (coinCount > 0) {
      lcd.print("Lahe, sa sastad!$");
    } else {
      lcd.print("Pane esimene munt!");
    }
  }

  delay(200);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
