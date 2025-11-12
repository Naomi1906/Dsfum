#define Do  131
#define Do_diez 139
#define Re  147
#define Re_diez 156
#define Mi  165
#define Fa  175
#define Fa_diez 185
#define Sol  196
#define Sol_diez 208
#define La  220
#define La_diez 233
#define Si  247

  int note[] = { // Twinkle Twinkle (singura melodie pe care m a invatat-o cineva la pian)
  C4,4, C4,4, G4,4, G4,4, A4,4, A4,4, G4,8,
  F4,4, F4,4, E4,4, E4,4, D4,4, D4,4, C4,8,
  G4,4, G4,4, F4,4, F4,4, E4,4, E4,4, D4,8,
  G4,4, G4,4, F4,4, F4,4, E4,4, E4,4, D4,8,
  C4,4, C4,4, G4,4, G4,4, A4,4, A4,4, G4,8,
  F4,4, F4,4, E4,4, E4,4, D4,4, D4,4, C4,8}; 


void setup() {
    int octava=1; // puteti schimba cu 2,4,8 pentru a incerca alta octava - uneori se aude mai bine
    int notesCount = sizeof(note) / sizeof(note[0]) / 2;

    for (int nota_curenta = 0; nota_curenta < notesCount; nota_curenta++) 
    {
      tone(3, note[nota_curenta*2] * octava, 100*note[nota_curenta*2+1]); // 3 = pinul cu buzzer-ul, nota, delay
      delay(100*note[nota_curenta*2+1] + 100);
      noTone(3);
    }  
}

void loop() {
}

