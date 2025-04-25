int sensorPin = 0;  // Potentiomeetri analoog sisendi pin

int red = 13, yellow = 12, green = 11, red2 = 10;
int yellow2 = 9, green2 = 8;

int ledPins[] = {13, 12, 11, 10, 9, 8};

int lastPotValue = -1;  // Salvestame viimase potentiomeetri väärtuse
int currentPattern = 0; // Hoidke praegune LED mustri väärtus
int threshold = 10;     // Miinimum väärtuse muutus, et käivitada mustri vahetus

void setup() {
  // Algatame LED pin'id kui väljundid
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);  // Algatame sariväljundi (kui on vajalik)
}

void loop() {
  int potValue = analogRead(sensorPin);  // Loeme potentiomeetri väärtuse
  
  // Kontrollime, kas potentiomeetri väärtus on oluliselt muutunud
  if (abs(potValue - lastPotValue) > threshold) {
    lastPotValue = potValue; // Uuendame viimase potentiomeetri väärtuse
    
    // Vaatame, millist mustrit valida vastavalt potentiomeetri väärtusele
    currentPattern = map(potValue, 0, 1023, 0, 4);  // Mappige potentiomeetri väärtus mustri numbriks (0-4)
  }

  // Täidame vastava mustri, sõltuvalt praegusest mustrist
  switch (currentPattern) {
    case 0:
      vilguKogudega(200); // Muster 1: Kõik LED-id vilguvad koos
      break;
    case 1:
      vilguJargmisena(200); // Muster 2: LED-id vilguvad järjest
      break;
    case 2:
      vilguJuhuslikult(200); // Muster 3: LED-id vilguvad juhuslikult
      break;
    case 3:
      koguOn(1000); // Muster 4: Kõik LED-id on kauem sisse lülitatud
      break;
    case 4:
      vilguSensoriga(200); // Muster 5: LED-id vilguvad vastavalt potentiomeetri viivitusele
      break;
  }
}

// Muster 1: Kõik LED-id vilguvad koos
void vilguKogudega(int wait) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], HIGH); // Lülitame kõik LED-id sisse
  }
  delay(wait);  // Ootame määratud viivitusaja
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], LOW); // Lülitame kõik LED-id välja
  }
  delay(wait);  // Ootame määratud viivitusaja
}

// Muster 2: LED-id vilguvad järjest
void vilguJargmisena(int wait) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], HIGH); // Lülitame LED sisse
    delay(wait);  // Ootame määratud viivitusaja
    digitalWrite(ledPins[i], LOW); // Lülitame LED välja
  }
}

// Muster 3: LED-id vilguvad juhuslikult
void vilguJuhuslikult(int wait) {
  for (int i = 0; i < 6; i++) {
    int randomPin = random(0, 6);  // Juhuslikult valitud LED pin
    digitalWrite(ledPins[randomPin], HIGH); // Lülitame valitud LED sisse
    delay(wait);  // Ootame määratud viivitusaja
    digitalWrite(ledPins[randomPin], LOW); // Lülitame valitud LED välja
  }
}

// Muster 4: Kõik LED-id on kauem sisse lülitatud
void koguOn(int wait) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], HIGH); // Lülitame kõik LED-id sisse
  }
  delay(wait);  // Ootame määratud viivitusaja
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], LOW); // Lülitame kõik LED-id välja
  }
}

// Muster 5: LED-id vilguvad vastavalt potentiomeetri viivitusajale
void vilguSensoriga(int wait) {
  int sensorValue = analogRead(sensorPin); // Loeme taas potentiomeetri väärtuse
  float mult = sensorValue / 1023.0;  // Normaliseerime väärtus vahemikku 0-1
  int delayTime = 50 + mult * 500;  // Viivitus põhineb potentiomeetri väärtusel (50-550ms vahemik)
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], HIGH); // Lülitame LED sisse
    delay(delayTime);  // Ootame määratud viivitusaja
    digitalWrite(ledPins[i], LOW); // Lülitame LED välja
    delay(delayTime);  // Ootame määratud viivitusaja
  }
}
