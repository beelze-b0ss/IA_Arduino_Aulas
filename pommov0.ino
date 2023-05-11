const int potentiometerPin = A0;
int buttonValue = 0;
const int buttonPin = 3;
const int ledPin = 2;
const int intervalosSessao[4] = {15, 20, 25, 30};
int intervalo = 0; 
int potValue = 0;

void setup() {
  pinMode(potentiometerPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 
  buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);

  if(buttonValue != 0){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
 
 potValue = analogRead(A0);

  if (potValue >= 0 && potValue < 256) {
    intervalo = intervalosSessao[3];
  } else if (potValue >= 256 && potValue < 512) {
    intervalo = intervalosSessao[2];
  } else if (potValue >= 512 && potValue < 768) {
    intervalo = intervalosSessao[1];
  } else if (potValue >= 768 && potValue <= 1023) {
    intervalo = intervalosSessao[0];
  }


  char output[20];
  sprintf(output, "sessao de %d minutos", intervalo);

  Serial.println(output);
}
