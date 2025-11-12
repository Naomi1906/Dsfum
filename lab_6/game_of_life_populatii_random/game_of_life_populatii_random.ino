
// prima oara vom memora pozitiile la care este conectata matricea:
int MOSI_pin = 11;
int SlaveSelect_pin = 10;
int Clock_pin = 13;


// apoi stabilim cateva zone memorabile din max:
byte max7219_reg_noop        = 0x00; // nu face nimic
byte max7219_reg_digit0      = 0x01; // seteaza primul rand
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

int a[8][8]; // generatie curenta
int b[8][8]; // generatie viitoare
int c[8][8]; // generatie dinainte

int pauza = 250; // intre generatii

void putByte(byte data) { // trebuie sa scriem bitii din data pe rand, de la stg la dreapta, sincronizat
  for (int i=7; i>=0; i--)
  {  
    digitalWrite(Clock_pin, LOW);   // incepe o scriere sincronizata
    digitalWrite(MOSI_pin, (data & (0x01 << i)) ? HIGH : LOW); // cand i=7 scriu cel mai din stg bit din data...
    digitalWrite(Clock_pin, HIGH);   // a terminat sincronismul
  }
}
void toMax( byte reg, byte col) {    
  digitalWrite(SlaveSelect_pin, LOW);       // selectez slaveul    
  putByte(reg);                  // ii zic in ce zona de memorie scriu
  putByte(col);                  // si scriu valoarea
  digitalWrite(SlaveSelect_pin,HIGH);       // deselectez slaveul ca sa activez ce am scris
}

void resetmatrix(int m[8][8]){
  for (int i=0; i<8; i++)
     for(int j=0; j<8; j++)
        m[i][j]=0;
}


void displayMatrix(int m[8][8]){
   for(int i=0; i<8; i++)
   {
      int val = 0;
      for(int j=0; j<8; j++)
      {
        val |= (m[i][7-j]<<j); 
      }
      toMax(i+1,val);
   }  
}
void generateRandomPopulation(){
  resetmatrix(a);
  // aleg random niste celule care sa fie aprinse
  int n = random(8, 20);
  for(int i=0;i<n;i++){
    a[random(0,8)][random(0,8)]=1;
  }
}

int countNeighbors(int x, int y, int m[8][8]){
  int cnt = 0;
  for(int dx=-1; dx<=1; dx++){
    for(int dy=-1; dy<=1; dy++){
      if(dx==0 && dy==0) continue;
      int nx = x + dx;
      int ny = y + dy;
      if(nx>=0 && nx<8 && ny>=0 && ny<8){
        if(m[nx][ny]) cnt++;
      }
    }
  }
  return cnt;
}

bool equalMatrices(int m1[8][8], int m2[8][8]){
  for(int i=0;i<8;i++) for(int j=0;j<8;j++) if(m1[i][j]!=m2[i][j]) return false;
  return true;
}

void copyMatrix(int src[8][8], int dst[8][8]){
  for(int i=0;i<8;i++) for(int j=0;j<8;j++) dst[i][j]=src[i][j];
}

void flashAndReset(){
  // sting si aprind ca sa se vada ca i dau reset
  for(int t=0;t<3;t++){
    for (int i=1;i<=8;i++) toMax(i,0xFF);
    delay(80);
    for (int i=1;i<=8;i++) toMax(i,0x00);
    delay(80);
  }
  generateRandomPopulation();
}

void setup() {
  Serial.begin(9600);
  pinMode(MOSI_pin, OUTPUT);
  pinMode(Clock_pin,  OUTPUT);
  pinMode(SlaveSelect_pin,   OUTPUT);

  digitalWrite(Clock_pin, HIGH);

  toMax(max7219_reg_scanLimit, 0x07);
  toMax(max7219_reg_decodeMode, 0x00);
  toMax(max7219_reg_shutdown, 0x01);
  toMax(max7219_reg_displayTest, 0x00);
  for (int i=1; i<=8; i++) toMax(i,0);
  toMax(max7219_reg_intensity, 0x08); 

  randomSeed(analogRead(0));
  generateRandomPopulation();
  resetmatrix(c); // generatie anterioara = zero
}

void loop() {
  // afisez generatia curenta
  displayMatrix(a);
  delay(pauza);

  // calcul generatia urmatoare in b
  resetmatrix(b);
  for(int x=0;x<8;x++){
    for(int y=0;y<8;y++){
      int neighbors = countNeighbors(x,y,a);
      if(a[x][y]==1){
        // regula: 2 sau 3 -> supravietuieste
        if(neighbors==2 || neighbors==3) b[x][y]=1; else b[x][y]=0;
      } else {
        // regula: 3 -> nastere
        if(neighbors==3) b[x][y]=1; else b[x][y]=0;
      }
    }
  }

  // detectie stari terminale sau oscilatii de perioada 2
  bool stable = equalMatrices(a,b);      // nu se schimba
  bool oscillation2 = equalMatrices(b,c); // intoarce la c -> perioada 2

  // cand sunt toate 0
  int sum=0; for(int i=0;i<8;i++) for(int j=0;j<8;j++) sum += b[i][j];
  bool dead = (sum==0);

  if(stable || oscillation2 || dead){
  //de la capat
    Serial.println("Detected stable/oscillation/dead -> autoreset");
    flashAndReset();
    // actualizam c cu generatie curenta, apoi sarim la noua generatie (generateRandomPopulation deja scrie in a)
    resetmatrix(c);
    return; // afisam imediat noua populatie in urmatorul loop
  }
  copyMatrix(a, c);
  copyMatrix(b, a);
}
