const int RED_PIN = 13;
const int YELLOW_PIN = 12;
const int GREEN_PIN = 11;
const int DAY_PIN = 8;
const int NIGHT_PIN = 7;

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(DAY_PIN, OUTPUT);
  pinMode(NIGHT_PIN, OUTPUT);
}

void loop()
{
  // tee kaks päeva tsüklid ja üks öö tsükkel
  paev();
  paev();
  oo();
}

void paev()
{
  //Lülita sisse päev indikaator led
  digitalWrite(DAY_PIN, HIGH);

  // põleb punane ja siis põleb kollane
  digitalWrite(RED_PIN, HIGH);
  delay(1500);
  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);
  // punane ja kollane on välja lülitatud
  // roheline põleb
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(1500);
  //roheline vilgub
  for (int i = 0; i < 6; i++) {
    digitalWrite(GREEN_PIN, HIGH);
    delay(300);
    digitalWrite(GREEN_PIN, LOW);
    delay(300);
  }
  //kollane põleb
  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);
  digitalWrite(YELLOW_PIN, LOW);

  // Lülita välja päeva indikaator led
  digitalWrite(DAY_PIN, LOW);
}

void oo()
{
  // öö led indikaator põleb
  digitalWrite(NIGHT_PIN, HIGH);

  // kollane vilgub
  for (int i = 0; i < 12; i++) {
    digitalWrite(YELLOW_PIN, HIGH);
    delay(300);
    digitalWrite(YELLOW_PIN, LOW);
    delay(300);
  }

  // öö led indikaator on välja lülitatud
  digitalWrite(NIGHT_PIN, LOW);
}
