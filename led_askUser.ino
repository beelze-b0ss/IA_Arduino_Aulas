#define LED_PIN 9
int times;             
long duration;          

void setup() {
  pinMode(LED_PIN, OUTPUT);   
  Serial.begin(9600);        
}

void loop() {
  Serial.println("insira vezes");

  while (!Serial.available()) {
  }

  // lê o times
  times = Serial.parseInt();
  Serial.read();

  Serial.println("insira tempo");
  // espera novamente
  while (!Serial.available()) {
  }
  
  // lê duração
  duration = Serial.parseInt();
  Serial.read();
  
  // pisca
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);    
    delay(duration);               
    digitalWrite(LED_PIN, LOW);     
    delay(duration);               
  }
}
