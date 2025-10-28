const int ledPin = 8;
int ledState = LOW;
unsigned long prevTime = 0;
bool blink = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("1 - pornit, 2 -oprit, 3 - blink");
}

void loop() {
  if (Serial.available() > 0) {
    char option = Serial.read(); 
    if (option == '\n' || option == '\r') return;

    switch (option) {
      case '1':
        Serial.println("pornit");
        digitalWrite(ledPin, HIGH);
        blink = false; 
        break;

      case '2':
        Serial.println("oprit");
        digitalWrite(ledPin, LOW);
        blink = false;
        break;

      case '3':
        Serial.println("blink");
        blink = true;
        break;

      default:
        Serial.println("not an option");
        break;
    }
  }

  if (blink) {
    unsigned long now = millis();
    if (now - prevTime >= 500) {
      prevTime = now;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }
}
