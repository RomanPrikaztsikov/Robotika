const int sensorPin = A0;  // Fotoresistor A0-l
const int ledPin = 9;      // LED pinil 9

void setup() {
  pinMode(ledPin, OUTPUT);     // Seadista LED väljundiks
  Serial.begin(9600);          // Alusta seriemonitori
}

void loop() {
  int lightLevel = analogRead(sensorPin);  // Loe fotoresistori väärtus

  Serial.println(lightLevel);  // Prindi valguse väärtus silumiseks

  if (lightLevel > 600) {      // Kui on pime (kõrgem väärtus)
    digitalWrite(ledPin, HIGH); // Lülita LED sisse
  } else {
    digitalWrite(ledPin, LOW);  // Lülita LED välja
  }

  delay(100);  // Väike viivitus
}
