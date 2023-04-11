//port 8 -> topo
//port 9 -> 

char ledPins[] = {
  8, 9, 10, 11, 12, 13, A5, A4
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {

  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(500);
  }
  delay(2000);
  clearDisplay();
}

void clearDisplay() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
