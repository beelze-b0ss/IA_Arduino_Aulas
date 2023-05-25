const int potentiometerPin = A0;
const int intervalosSessao[4] = {1, 2, 3, 4};
const int numCiclo[4] = {1, 2, 3, 4};
int ciclo = 0;
int intervalo = 0;
int potValue = 0;

const int buttonPin = 2;  // the number of the pushbutton pin
const int buttonPinB = 3; //suspende a sessão

unsigned long startTime = 0;  // variable to store the start time of the timer
bool timerStarted = false;  // flag to track if the timer has started
bool pauseTimer = false;
int buttonState = 0;

const int ledPinA = 12;
const int ledPinB = 13;

const int pinFaseA = 7;
const int pinFaseB = 8;
const int pinFaseC = 9;
const int pinFaseD = 10;

bool primeiroClique = true;
unsigned long tempoPausa = 5000;  // 5 segundos de pausa
unsigned long tempoPausaInicio = 0;

void setup() {
  pinMode(potentiometerPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(pinFaseA, OUTPUT);
  pinMode(pinFaseB, OUTPUT);
  pinMode(pinFaseC, OUTPUT);
  pinMode(pinFaseD, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(A0);
  buttonState = digitalRead(buttonPin);

  if (potValue >= 0 && potValue < 256) {
    intervalo = intervalosSessao[0];
  } else if (potValue >= 256 && potValue < 512) {
    intervalo = intervalosSessao[1];
  } else if (potValue >= 512 && potValue < 768) {
    intervalo = intervalosSessao[2];
  } else if (potValue >= 768 && potValue <= 1023) {
    intervalo = intervalosSessao[3];
  }

  unsigned long tempoSegundos = intervalo * 1000;

  if (buttonState == HIGH && primeiroClique) {
    startTime = millis();
    timerStarted = true;
    primeiroClique = false;
    Serial.println("Timer started!");
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, LOW);
  }

  if (timerStarted && millis() - startTime >= tempoSegundos) {
    timerStarted = false;
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, LOW);
    ciclo += 1;

    if (ciclo < 4) {
      primeiroClique = true;
      tempoPausaInicio = millis();
    } else {
      ciclo = 0;
      primeiroClique = true;
    }
  }

  if (primeiroClique && millis() - tempoPausaInicio >= tempoPausa) {
    primeiroClique = false;
    startTime = millis();
    timerStarted = true;
    Serial.println("Pausa started!");
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, LOW);
  }

  if (timerStarted) {
    unsigned long elapsedTime = millis() - startTime;
    Serial.print("Elapsed time: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, HIGH);
  }

  if (timerStarted) {
    if (ciclo >= 0 && ciclo < 4) {
      for (int i = 0; i <= ciclo; i++) {
        switch (numCiclo[i]) {
          case 1:
            digitalWrite(pinFaseA, HIGH);
            digitalWrite(pinFaseB, LOW);
            digitalWrite(pinFaseC, LOW);
            digitalWrite(pinFaseD, LOW);
            break;
          case 2:
            digitalWrite(pinFaseA, HIGH);
            digitalWrite(pinFaseB, HIGH);
            digitalWrite(pinFaseC, LOW);
            digitalWrite(pinFaseD, LOW);
            break;
          case 3:
            digitalWrite(pinFaseA, HIGH);
            digitalWrite(pinFaseB, HIGH);
            digitalWrite(pinFaseC, HIGH);
            digitalWrite(pinFaseD, LOW);
            break;
          case 4:
            digitalWrite(pinFaseA, HIGH);
            digitalWrite(pinFaseB, HIGH);
            digitalWrite(pinFaseC, HIGH);
            digitalWrite(pinFaseD, HIGH);
            break;
          default:
            // Handle an invalid numCiclo value
            break;
        }
      }
    }
  }
}
