int led = 9;
int brightness = 0;
int fadeAmount = 1;            
unsigned long prevTime = 0;  
int fadeInterval = 10;   

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("viteza: ");
}

void loop() {
  if (Serial.available() > 0) {
    int val = Serial.parseInt();
    if (val > 0) {
      fadeInterval = val;
      Serial.println(fadeInterval);
    }
  }
  unsigned long now = millis();
  
  if (now - prevTime >= fadeInterval) {
    prevTime = now;

    analogWrite(led, brightness);
    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;  
    }
  }
}
