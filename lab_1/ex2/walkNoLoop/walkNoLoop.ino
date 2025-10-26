unsigned long prevTime = 0;
int animationState = 0;
int direction = 1;
int currentLed = 8;   

void setup() {
  for (int i = 8; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void allOff() {
  for (int i = 8; i <= 13; i++)
    digitalWrite(i, LOW);
}

void blink() {
  static bool on = false;
  if (millis() - prevTime >= 500) {
    prevTime = millis();
    on = !on;
    for (int i = 8; i <= 13; i++)
      digitalWrite(i, on);

    if (!on) { 
      animationState = 1;
      allOff();
    }
  }
}

void breakSec() {
  if (millis() - prevTime >= 500) {
    prevTime = millis();
    animationState = 2;
    allOff();
  }
}

void move() {
  static byte pattern = 0b000001; 
  static bool toRight = true;    
  static bool endAn = false;

  if (millis() - prevTime >= 100) {
    prevTime = millis();

    for (int i = 0; i < 6; i++) {       
      digitalWrite(8 + i, (pattern >> i) & 1);
    }

    if (toRight){
      if (pattern == 0b100000) toRight = false;
      pattern <<= 1;
    }
    else{
      if (pattern == 0b000001) endAn = true;
      pattern >>= 1;
    }
    if (endAn){
      allOff();               
      animationState = 3;    
      pattern = 0b000001;
      toRight = true;
      endAn = false;
    }
}}


void loop() {
  switch(animationState) {
    case 0: blink(); break;
    case 1: breakSec(); break;
    case 2: move(); break;
    case 3:
      if (millis() - prevTime >= 500) {
        prevTime = millis();
        animationState = 0;
      }
      break;
  }
}

