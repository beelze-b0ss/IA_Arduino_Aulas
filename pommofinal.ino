// Constantes
const int pinPotenciometro = A0;
const int intervalosSessao[4] = {15, 20, 25, 30};
const int numCiclo[4] = {1, 2, 3, 4};
const int botaoIniciar = 2;
const int botaoInterromper = 3;
const int ledPinVerde = 12;
const int ledPinVermelho = 13;
const int pinFases[4] = {7, 8, 9, 10};
const int pinInterrupt = 11;
const unsigned long tempoPausa = 5 * 60000; //5 minutos em milisegundos

// Variáveis globais
int ciclo = 0;
int intervalo = 0;
int valorPotencia = 0;
unsigned long startTime = 0;
bool timerIniciado = false;
bool primeiroClique = false;
unsigned long tempoPausaInicio = 0;

void setup() {
  // Configuração dos pins
  pinMode(pinPotenciometro, INPUT);
  pinMode(botaoIniciar, INPUT_PULLUP);
  pinMode(botaoInterromper, INPUT_PULLUP);
  pinMode(ledPinVerde, OUTPUT);
  pinMode(ledPinVermelho, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(pinFases[i], OUTPUT);
  }
  pinMode(pinInterrupt, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  valorPotencia = analogRead(pinPotenciometro);

  // Verifica o estado dos botões
  bool botaoIniciarPressionado = digitalRead(botaoIniciar) == HIGH;
  bool botaoInterromperPressionado = digitalRead(botaoInterromper) == HIGH;

  if (botaoInterromperPressionado) {
    if (timerIniciado) {
      // Armazena o tempo decorrido antes da suspensão
      unsigned long tempoPassado = millis() - startTime;
      startTime = millis();
      timerIniciado = false;
    }
    primeiroClique = false;
    digitalWrite(pinInterrupt, HIGH);
  }

  // Determina o intervalo com base no valor do potenciômetro
  if (valorPotencia >= 0 && valorPotencia < 256) {
    intervalo = intervalosSessao[0];
  } else if (valorPotencia >= 256 && valorPotencia < 512) {
    intervalo = intervalosSessao[1];
  } else if (valorPotencia >= 512 && valorPotencia < 768) {
    intervalo = intervalosSessao[2];
  } else if (valorPotencia >= 768 && valorPotencia <= 1023) {
    intervalo = intervalosSessao[3];
  }

  unsigned long tempoMilisegundos = intervalo * 60000; // intervalo x quantos ms existem num minuto = tempo em ms

  if (botaoIniciarPressionado) {
    primeiroClique = true;
    digitalWrite(pinInterrupt, LOW);
  }

  if (botaoIniciarPressionado && primeiroClique) {
    unsigned long tempoPassado = 0;
    if (!timerIniciado) {
      // Ajusta o tempo de início subtraindo o tempo decorrido
      startTime = millis() - tempoPassado;
    }
    timerIniciado = true;
    primeiroClique = false;
    Serial.println("Timer iniciado!");
    atualizarLEDs(true, false);
  }

  if (timerIniciado && millis() - startTime >= tempoMilisegundos) {
    timerIniciado = false;
    atualizarLEDs(true, false);
    ciclo += 1;

    if (ciclo < 4) {
      primeiroClique = true;
      tempoPausaInicio = millis();
    } else if (ciclo == 4) {
      primeiroClique = true;
      tempoPausaInicio = millis();
      desligarFases();
    } else {
      ciclo = 0;
      primeiroClique = true;
    }
  }

  if (primeiroClique && millis() - tempoPausaInicio >= tempoPausa) {
    primeiroClique = false;
    startTime = millis();
    timerIniciado = true;
    Serial.println("Pausa iniciada!");
    atualizarLEDs(true, false);
  }

  if (timerIniciado) {
    unsigned long tempoPassado = millis() - startTime;
    Serial.print("Tempo decorrido: ");
    Serial.print(tempoPassado);
    Serial.println(" ms");
    atualizarLEDs(false, true);
  }

  if (timerIniciado && ciclo >= 0 && ciclo < 4) {
    for (int i = 0; i <= ciclo; i++) {
      digitalWrite(pinFases[i], HIGH);
    }
  }
}

void atualizarLEDs(bool ledVerdeLigado, bool ledVermelhoLigado) {
  digitalWrite(ledPinVerde, ledVerdeLigado ? HIGH : LOW);
  digitalWrite(ledPinVermelho, ledVermelhoLigado ? HIGH : LOW);
}

void desligarFases() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pinFases[i], LOW);
  }
}
