const int ledPin = 8;       
int brightness = 0;          
int fadeAmount = 1;          
const int period = 20;       
unsigned long prevStep = 0;  

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  int on = (brightness * period) / 255;
  if ((now % period) < on) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  if (now - prevStep >= 2) {
    prevStep = now;
    brightness += fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;  
  }
  }
}
