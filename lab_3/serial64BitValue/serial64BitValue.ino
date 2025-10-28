String inputString = "";   // pentru a reține ce tastezi
bool inputComplete = false;

void allOff() {
  for (int i = 8; i <= 13; i++)
    digitalWrite(i, LOW);
}
void setup() {
  Serial.begin(9600);
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.println("introduceti o valoare:");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {   
      inputComplete = true;
    } else if (isDigit(c)) {        
      inputString += c;
    }else { 
      Serial.println("doar numere");
      inputString = "";
      }
  }

  if (inputComplete) {
    int valoare = inputString.toInt();  
    if (valoare >= 0 && valoare < 64) {
      for (int i = 0; i < 6; i++) {
        int bitVal = (valoare >> i) & 1;
        digitalWrite(i + 8, bitVal);
      }
      Serial.println("Valoare: ");
      Serial.println(valoare);
    } else {
      Serial.println("doar intre 0 si 63");
      allOff();
    }
    inputString = "";
    inputComplete = false;
  }
}
