#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A1;
const int lightPin = A0;
const int humidityPin = A2;
const int buzzerPin = 8;

float temperature;
float voltage;
float degreesF;
int lightLevel;
int humidityLevel;

unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long lastEmojiShowTime = 0;
const long emojiInterval = 10000;
unsigned long lastDegreeSwitch = 0;
bool fDegrees = false; // määrab, kas näidata temperatuuri Fahrenheiti kraadides

bool danger = false;
bool lastDangerState = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(tempPin, INPUT);
  pinMode(lightPin, INPUT);
  pinMode(humidityPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // kontrollime, kas on möödunud vähemalt üks sekund andmete uuendamiseks
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    lightLevel = analogRead(lightPin); // valguse taseme lugemine
    voltage = getVoltage(tempPin);     // teisendame temperatuuriandurilt saadud väärtuse pingeks
    temperature = (voltage - 0.5) * 100.0; // teisendame pinge kraadideks Celsiuses
    degreesF = temperature * (9.0 / 5.0) + 32.0; // teisendame Celsiuse Fahrenheiti

    humidityLevel = analogRead(humidityPin); // loeme "niiskuse" anduri väärtust (eeldatavasti analoogandur)

    // kontrollime ohuolukorda – kas temperatuur on liiga kõrge või valgus liiga madal
    danger = false;
    if (temperature > 30 || lightLevel < 100) {
      danger = true;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");

    // vahetame iga poole sekundi järel, kas kuvatakse temperatuuri F või C
    if (currentMillis - lastDegreeSwitch > 500) {
      lastDegreeSwitch = currentMillis;
      fDegrees = !fDegrees;
    }

    if (fDegrees) {
      lcd.print(degreesF, 1);
      lcd.print(" F");
    } else {
      lcd.print(temperature, 1);
      lcd.print(" C");
    }

    lcd.setCursor(0, 1);
    lcd.print("L:");
    lcd.print(1023 - lightLevel); // inverteerime valguse taseme, nii et suurem number = rohkem valgust
    lcd.print(" H:");
    lcd.print(humidityLevel / 10); // lihtne teisendus, et näidata väiksemat ja loetavamat niiskuse taset

    // kui olek muutus ohutuks ja see oli eelnevalt turvaline, käivitame alarmi
    if (danger && !lastDangerState) {
      playAlarm();
    }

    lastDangerState = danger; // salvestame hetke ohuolukorra järgmise tsükli jaoks
  }
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814); // teisendab analoogväärtuse pingeks (5V/1024)
}

void playAlarm() {
  // Mängib häiresignaali kolm korda lühikeste vahedega
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000, 200);
    delay(250);
  }
  noTone(buzzerPin);
}
