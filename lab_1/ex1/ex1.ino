void setup() {
  for(int i=8;i<=13;i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for(int i=8;i<=13;i++) {
  digitalWrite(i, 1);   
  }
  delay(300);
  for(int i=8;i<=13;i++) {
  digitalWrite(i, 0);
  }                        
  delay(300); 
}


