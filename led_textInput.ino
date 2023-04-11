int ledPin = 9; 
String ledState; 


void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); 
} 

void loop() {

  if (Serial.available()) {     
    ledState = Serial.readString(); 
    ledState.trim(); 
    
    if (ledState.equals("On")) { 
      Serial.println("Led On!"); 
      digitalWrite(ledPin, HIGH);     
    } 
    
    if (ledState.equals("Off")) { 
      Serial.println("Led Off :("); 
      digitalWrite(ledPin, LOW);     
    }   
  } 
} 
