#define LED_PIN 11
#define LED_PINTWO 10
#define POTENTIOMETER_PIN A1

int mapPotentiometerValue(int potValue){
  int brightness = potValue / 4;
  return brightness;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PINTWO, OUTPUT);
}

void loop()
{
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  int brightness = mapPotentiometerValue(potentiometerValue);
  
  analogWrite(LED_PIN, brightness);
  analogWrite(LED_PINTWO, brightness);
}
