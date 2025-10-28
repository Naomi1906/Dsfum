int led = 9;
int brightness = 0;
int fadeAmount = 1;            
unsigned long prevTime = 0;    

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  
  if (now - prevTime >= 10) {
    prevTime = now;

    analogWrite(led, brightness);
    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;  
    }
  }
}
