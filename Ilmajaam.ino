#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A1;
const int lightPin = A0;

float temperature;
float voltage;
float degreesF;
int lightLevel;

unsigned long previousMillis = 0;
const long interval = 1000;  // Sensorite lugemiseks määratud intervall
unsigned long emojiMillis = 0;
const long emojiInterval = 10000; // Aeg, mis määrab emoji kuvamise sageduse
unsigned long lastEmojiShowTime = 0;
unsigned long lastDegreeSwitch = 0;
bool fDegrees = false;  // Kas kuvada temperatuuri Celsiuse või Fahrenheiti järgi

void setup() {
  lcd.begin(16, 2); // Algatame LCD ekraani
  pinMode(tempPin, INPUT);  // Temperatuurianduri sisendi seadistamine
  pinMode(lightPin, INPUT);  // Valgustundliku sensori sisendi seadistamine
}

void loop() {
  unsigned long currentMillis = millis();  // Aeg, mis on möödunud seadme käivitamisest

  // Kui on möödunud piisavalt aega, loeme sensoreid ja värskendame ekraani
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    lightLevel = analogRead(lightPin);  // Valgustunde lugemine
    voltage = getVoltage(tempPin);  // Temperatuurianduri pinge lugemine
    temperature = (voltage - 0.5) * 100.0;  // Arvutame temperatuuri sensorist saadud pinge põhjal
    degreesF = temperature * (9.0 / 5.0) + 32.0;  // Teisendame temperatuuri Celsiuse järgi Fahrenheiti

    lcd.clear();  // Tühjendame ekraani enne uut teavet
    lcd.setCursor(0, 0);  // Paigutame kursor esimesele reale
    lcd.print("Temp: ");
    
    // Iga 500 ms tagant vahetame temperatuuri ühikut
    if (currentMillis - lastDegreeSwitch > 500) {
      lastDegreeSwitch = currentMillis;
      fDegrees = !fDegrees;  // Vahetame temperatuuri kuvamise ühiku
    }

    // Kuvame temperatuuri vastavalt valitud ühikule
    if (fDegrees) {
      lcd.print(degreesF, 1);  // Kuvame temperatuuri Fahrenheiti järgi
      lcd.print(" F");
    } else {
      lcd.print(temperature, 1);  // Kuvame temperatuuri Celsiuse järgi
      lcd.print(" C");
    }

    lcd.setCursor(0, 1);  // Paigutame kursor teisele reale
    lcd.print("Light: ");
    lcd.print(lightLevel);  // Kuvame valgustunde taseme
    lcd.print(" lx");
  }

  // Kuvame emojit iga 10 sekundi tagant, sõltuvalt temperatuurist
  if (currentMillis - lastEmojiShowTime >= emojiInterval) {
    lastEmojiShowTime = currentMillis;

    lcd.clear();  // Tühjendame ekraani enne uue emotikoni kuvamist
    lcd.setCursor(6, 0);  // Paigutame kursor emojile sobivasse kohta
    if (temperature > 25) {
      lcd.print(":)");  // Kuvame naeratava näo, kui temperatuur on üle 25°C
    } else {
      lcd.print(":(");  // Kuvame kurva näo, kui temperatuur on alla 25°C
    }

    delay(1000);  // Paus enne järgmise emotikoni kuvamist
  }
}

// Arvutame analoogpinge väärtusest tegeliku pinge
float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);  // Muundame analoog väärtuse pinge väärtuseks
}

