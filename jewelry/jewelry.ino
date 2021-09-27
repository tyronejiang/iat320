int LED1=9;
int LED2=10;
int brightness = 0;    
int fadeAmount = 5;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // fade part
  
   while (brightness < 255) {
      brightness = brightness + fadeAmount;
      analogWrite(LED1, brightness);
      analogWrite(LED2, brightness);
      delay(30);
    }
    fadeAmount = -fadeAmount;
    while (brightness > 0) {
      brightness = brightness + fadeAmount;
      analogWrite(LED1, brightness);
      analogWrite(LED2, brightness);
      delay(30);
    }
    fadeAmount = -fadeAmount;
   
  delay(500);  

  // blink part
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW); 
  delay(500);    
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW); 
  delay(500);   
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW); 
  delay(500);    
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW); 
  delay(500);  
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
  delay(500);
  
                  
  
}
