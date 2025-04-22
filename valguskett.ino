int sensorPin = 0;  // Analoogse sisendi pin sensorile

int red1 = 13, green1 = 12, orange1 = 11, blue1 = 10;
int red2 = 9, green2 = 8, orange2 = 7, blue2 = 6;

int ledPins[] = {13, 12, 11, 10, 9, 8, 7, 6};

void setup() {
  // Algatame LED pin'id kui väljundid
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int delayTime = getDelay();

  // Muster 1: Kõik LED-id vilguvad koos
  vilguKogudega(delayTime);

  // Muster 2: LED-id vilguvad järjest
  vilguJargmisena(delayTime);

  // Muster 3: LED-id vilguvad juhuslikult
  vilguJuhuslikult(delayTime);

  // Muster 4: Kõik LED-id on kauem sisse lülitatud
  koguOn(1000);

  // Muster 5: LED-id vilguvad sensorist saadud viivitusajaga
  vilguSensoriga(delayTime);
}

// Muster 1: Kõik LED-id vilguvad koos
void vilguKogudega(int wait) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(wait);
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(wait);
}

// Muster 2: LED-id vilguvad järjest
void vilguJargmisena(int wait) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(wait);
    digitalWrite(ledPins[i], LOW);
  }
}

// Muster 3: LED-id vilguvad juhuslikult
void vilguJuhuslikult(int wait) {
  for (int i = 0; i < 8; i++) {
    int randomPin = rand() % 8;  // Juhuslikult valitud LED pin
    digitalWrite(ledPins[randomPin], HIGH);
    delay(wait);
    digitalWrite(ledPins[randomPin], LOW);
  }
}

// Muster 4: Kõik LED-id on kauem sisse lülitatud
void koguOn(int wait) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(wait);
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Muster 5: LED-id vilguvad sensorist saadud viivitusajaga
void vilguSensoriga(int wait) {
  int sensorValue = analogRead(sensorPin);
  float mult = sensorValue / 1023.0;
  int delayTime = 50 + mult * 500;  // Viivitus varieerub vastavalt sensorile
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
}

// Funktsioon viivituse aja määramiseks sensorist lähtudes
int getDelay() {
  int sensorValue = analogRead(sensorPin);
  float mult = sensorValue / 1023.0;
  return 50 + mult * 500;
}

