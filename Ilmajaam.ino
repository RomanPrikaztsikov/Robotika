#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A1;  
const int lightPin = A0; 

float temperature;
float voltage;
float degreesF;
int lightLevel;

unsigned long previousMillis = 0;
const long interval = 1000; 
unsigned long emojiMillis = 0;
const long emojiInterval = 10000; 
unsigned long lastEmojiShowTime = 0;
unsigned long lastDegreeSwitch = 0;
bool fDegrees = false;

void setup() {
  lcd.begin(16, 2);  // Initsialiseerib LCD ekraani
  pinMode(tempPin, INPUT);  // Seadistab temperatuuri anduri sisendiks
  pinMode(lightPin, INPUT); // Seadistab valgusanduri sisendiks
}

void loop() {
  unsigned long currentMillis = millis(); 

  if (currentMillis - previousMillis >= interval) {  // Kontrollib, kas on möödunud piisavalt aega
    previousMillis = currentMillis;  

    lightLevel = analogRead(lightPin);  // Loe valguse taset
    voltage = getVoltage(tempPin);      // Arvuta temperatuuri anduri pinge
    temperature = (voltage - 0.5) * 100.0; // Arvuta temperatuur Celsiuses
    degreesF = temperature * (9.0/5.0) + 32.0; // Arvuta temperatuur Fahrenheiti järgi

    lcd.clear();  // Tühjenda ekraan
    lcd.setCursor(0, 0);  
    lcd.print("Temp: ");
    
    if (currentMillis - lastDegreeSwitch > 500) {  // Vaheta ühikut iga 500ms tagant
      lastDegreeSwitch = currentMillis; 
      fDegrees = !fDegrees; 
    }
    
    if (fDegrees) {
      lcd.print(degreesF, 1);  // Kuvab temperatuuri Fahrenheiti järgi
      lcd.print(" F");
    }
    else {
      lcd.print(temperature, 1);  // Kuvab temperatuuri Celsiuse järgi
      lcd.print(" C");
    }

    lcd.setCursor(0, 1);  
    lcd.print("Light: ");
    lcd.print(1023 - lightLevel);  // Kuvab valguse taseme (1023 - mõõdetud tase)
    lcd.print(" lx");
  }

  if (currentMillis - lastEmojiShowTime >= emojiInterval) {  // Emodži kuvamiseks, kui möödub 10 sekundit
    lastEmojiShowTime = currentMillis; 

    lcd.clear();  
    lcd.setCursor(6, 0);  // Aseta kursor ekraani keskossa
    if (temperature > 25) {  // Kui temperatuur on üle 25 kraadi, kuvab naeratuse
      lcd.print(":)");
    } else {  // Kui temperatuur on madalam või võrdne 25 kraadiga, kuvab kurva näo
      lcd.print(":(");
    }

    delay(1000);  // Oota 1 sekund enne järgmist emodži kuvamist
  }
}

// Arvuta pinge analooganduri lugemisest
float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);  // Muudab analooganduri väärtuse pingeks
}
