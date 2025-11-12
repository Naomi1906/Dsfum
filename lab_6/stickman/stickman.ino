#include <Arduino.h>

int MOSI_pin = 11;
int SlaveSelect_pin = 10;
int Clock_pin = 13;

// MAX7219 registre
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data){
  for(int i=7;i>=0;i--){
    digitalWrite(Clock_pin, LOW);
    digitalWrite(MOSI_pin, (data & (1<<i)) ? HIGH : LOW);
    digitalWrite(Clock_pin, HIGH);
  }
}

void toMax(byte reg, byte col){
  digitalWrite(SlaveSelect_pin, LOW);
  putByte(reg);
  putByte(col);
  digitalWrite(SlaveSelect_pin, HIGH);
}

void displayImage(uint64_t img){
  for(int row=0; row<8; row++){
    byte rowValue = 0;
    for(int col=0; col<8; col++){
      int bitIndex = row * 8 + col;         
      if(img & (1ULL << bitIndex)) rowValue |= (1 << col); 
    }
    toMax(row+1, rowValue);
  }
}




void setup(){
  Serial.begin(9600);
  pinMode(MOSI_pin, OUTPUT);
  pinMode(Clock_pin, OUTPUT);
  pinMode(SlaveSelect_pin, OUTPUT);
  digitalWrite(Clock_pin, HIGH);

  toMax(max7219_reg_scanLimit, 0x07);
  toMax(max7219_reg_decodeMode, 0x00);
  toMax(max7219_reg_shutdown, 0x01);
  toMax(max7219_reg_displayTest, 0x00);
  for(int i=1;i<=8;i++) toMax(i,0);
  toMax(max7219_reg_intensity, 0x08);

  Serial.println("Starting animation");
}

// stickman searching for light
uint64_t frames[] = {
  0x002214082a1c0800ULL,
  0x002214080a1c2800ULL,
  0x002214080a1c2880ULL,
  0x002214080a1ce8c0ULL,
  0x00221408081ceac0ULL,
  0x00221408081c2a00ULL,
  0x00221408281c0a00ULL
};

int numFrames = sizeof(frames)/sizeof(frames[0]);
int frameDelay = 300;

void loop(){
  for(int i=0;i<numFrames;i++){
    displayImage(frames[i]);

    // trimit pe serial asa pt ca nu suporta dimensiunea intreaga
    unsigned long high32 = frames[i] >> 32;
    unsigned long low32  = frames[i] & 0xFFFFFFFF;

    Serial.print("0x");
    Serial.print(high32, HEX);
    Serial.print(low32, HEX);
    Serial.println();

    delay(frameDelay);
  }
}
