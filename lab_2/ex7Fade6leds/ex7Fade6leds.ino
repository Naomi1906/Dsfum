const int numLEDs = 6;
const int ledPins[numLEDs] = {8, 9, 10, 11, 12, 13};

int brightness[numLEDs]; 
int fadeAmount[numLEDs]; 
int period = 20;         

unsigned long prevStep[numLEDs];
void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    brightness[i] = 1;       
    fadeAmount[i] = random(1, 5);        
    prevStep[i] = 0;
  }
}

void loop() {
  unsigned long now = millis();

  for (int i = 0; i < numLEDs; i++) {
    int on = (brightness[i] * period) / 255;
    if ((now % period) < on) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }

    if (now - prevStep[i] >= 2) {
      prevStep[i] = now;
      brightness[i] += fadeAmount[i];

      if (brightness[i] <= 0 || brightness[i] >= 255) {
        fadeAmount[i] = -fadeAmount[i]; 
      }
    }
  }
}
