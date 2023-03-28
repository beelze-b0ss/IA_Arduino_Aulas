#define BUZZER 10
#define BUZZER_TWO 11
#define POTENTIOMETER_PIN A1

int mapPotentiometerValue(int potValue){
  int brightness = potValue / 4;
  return brightness;
}

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(BUZZER_TWO, OUTPUT);
}

void loop()
{
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  int brightness = mapPotentiometerValue(potentiometerValue);
  tone(BUZZER, potentiometerValue );
  tone(BUZZER_TWO, potentiometerValue );
  
  analogWrite(BUZZER, brightness);
  analogWrite(BUZZER_TWO, brightness);
}
