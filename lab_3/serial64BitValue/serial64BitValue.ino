void setup() {
  Serial.begin(9600); 
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.println("valoare:");
}

void loop() {
  if (Serial.available() > 0) {      
    int valoare = Serial.parseInt();
    if (valoare >= 0 && valoare < 64) { 
      for (int i = 0; i < 6; i++) {
        int bitVal = (valoare >> i) & 1; 
        digitalWrite(i + 8, bitVal);
      }
      Serial.println(valoare);
    } else {
      Serial.println("trebuie intre 0 si 63");
    }
  }
}
