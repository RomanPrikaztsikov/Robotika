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
const long debounceDelay = 1000;

Servo servo;
LiquidCrystal lcd(6, 7, 9, 10, 11, 12);

// Parkimiskohtade ja olekute määramine
int parkingSpots = 5;
int currentCars = 0;
bool isBarrierOpen = false;
unsigned long lastCarTime = 0;
bool isParkingFull = false;
bool carDetected = false;
unsigned long lastActivationTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(redPin, OUTPUT);  
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  
  servo.attach(servoPin);    
  servo.write(closeAngle);  
  
  lcd.begin(16, 2);         
  lcd.print("Parkimissüsteem");
  delay(2000);            
  updateDisplay();        
  
  setRGBColor(0, 255, 0);   
}

void loop() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);   
  delayMicroseconds(2);         
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);        // Lühike impulss
  digitalWrite(trigPin, LOW);   // Lõpetab impulsi
  
  duration = pulseIn(echoPin, HIGH);  
  distance = duration * 0.034 / 2;  
  
  // Kui auto on avastatud
  if (distance <= detectionDist && distance > 0) {
    if (!carDetected && (millis() - lastActivationTime > debounceDelay)) {
      carDetected = true; 
      lastActivationTime = millis(); 
      
      if (!isBarrierOpen && !isParkingFull) {
        openBarrier();  // Avame tõkkepuu
        currentCars++; 
        if (currentCars >= parkingSpots) {
          isParkingFull = true;  // Kui parkimiskohad täis, siis lukk
        }
        updateDisplay(); 
      }
    }
    lastCarTime = millis(); 
  } else {
    carDetected = false; 
  }
  
  // Kui tõkkepuu on lahti ja auto on kadunud, sulgeme selle
  if (isBarrierOpen && (millis() - lastCarTime > sadTimeout)) {
    closeBarrier(); 
  }
  
  delay(100);
}

void openBarrier() {
  servo.write(openAngle); 
  isBarrierOpen = true;   
  setRGBColor(0, 0, 255);
  delay(1000);            
  setRGBColor(0, 255, 0);  
}

void closeBarrier() {
  servo.write(closeAngle); 
  isBarrierOpen = false;   
  setRGBColor(255, 0, 0); 
  delay(1000);    
  if (isParkingFull) {
    setRGBColor(255, 255, 0);  
  } else {
    setRGBColor(0, 255, 0);  
  }
}

void setRGBColor(int red, int green, int blue) {
  analogWrite(redPin, red);  
  analogWrite(greenPin, green); 
  analogWrite(bluePin, blue); 
}



void updateDisplay() {
  lcd.clear();  
  lcd.print("Vabu kohti: ");  // Kuvame vabad kohad
  lcd.print(parkingSpots - currentCars);  // Näitab, kui palju kohti on vabad
  lcd.print("/");
  lcd.print(parkingSpots);  // Näitab kokku parkimiskohti
  
  lcd.setCursor(0, 1);
  if (isParkingFull) {
    lcd.print("TÄIS!");  // Kui parkla on täis
  } else {
    lcd.print("Tere tulemast!");  // Kui veel ruumi
  }
}

