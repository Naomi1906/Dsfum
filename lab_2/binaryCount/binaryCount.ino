
void setup() {
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int n = 0; n < 64; n++) {
    for (int i = 0; i < 6; i++) {
      int bitVal = (n >> i) & 1; 
      digitalWrite(i+8, bitVal);
    }
    delay(500); 
  }
}
