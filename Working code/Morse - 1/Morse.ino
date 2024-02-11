// Georg Orlov Guðmundsson
// Fokk this klukkan er að ganga í 6 og er bara að fá stupid fokking villur maður
//
//
//
//
//

//Punktalengdir og delay, og init timer.
unsigned long buttonPressStartTime = 0;
const unsigned long dotThreshold = 25; // Threshold for a dot
const unsigned long dashThreshold = 70; // Threshold for a dash
int punktur = 25;
int strik = 70;
int delayMS = 10;
long timer = 0;

//Input-output setup.
const int Button = 32;
const int Prenta = 33;

//Annad.
unsigned long Start;
unsigned long End;
unsigned long Signal_Len = 0;
unsigned long Pause_Len = 0;
unsigned long Prenta_Len = 0;
bool dotPrinted = false;
bool donePrint = false;
bool donePrintStafur = false;
String geymsla = "";
String skil = "";

//Setur upp strúktur fyrir fylkið að neðan
struct MorseCodeSignal{
  char Letter; 
  String Signal;
};

//Fylkið sem inniheldur stafi og morse'inn þeirra
MorseCodeSignal MorseCode[26] = {
  {'A',".-"},   {'B',"-..."}, {'C',"-.-."}, {'D',"-.."},  {'E',"."},
  {'F',"..-."}, {'G',"--."},  {'H',"...."}, {'I',".."},   {'J',".---"},
  {'K',"-.-"},  {'L',".-.."}, {'M',"--"},   {'N',"-."},   {'O',"---"},
  {'P',".--."}, {'Q',"--.-"}, {'R',".-."},  {'S',"..."},  {'T',"-"},
  {'U',"..-"},  {'V',"...-"}, {'W',".--"},  {'X',"-..-"}, {'Y',"-.--"},
  {'Z',"--.."}
  };

//Setup
void setup() {
  Serial.begin(115200);
  //pinMode(Button, INPUT_PULLUP);
  pinMode(Button, INPUT);
  //attachInterrupt(digitalPinToInterrupt(Button), Signal_change, CHANGE);
}

//Leitar í gegnum fylkið til að finna réttan staf
char finnaStaf(String input){
  char stafur;
  for (int i=0;i<26;i++){
    if(MorseCode[i].Signal==geymsla) stafur=MorseCode[i].Letter;
  }
  return stafur;
}




//Ellert edition:
//Les og tekur tímann á tökkum. Þarf að endurbæta því takkarnir sökka, semsagt ekki hægt að ýtast oftar ein einu sinni á 10ms
void Signal_change() {
  if (digitalRead(Button) == 1) {
    timer++;
    delay(delayMS);
  } else{
    if(timer != 0){
    Serial.print("Tíminn er: ");
    Serial.println(timer);
    Prenta_Len = timer;
    timer=0;
    }
  }
  //Serial.println(timer);
 // if (digitalRead(Prenta) == 1){
 //   Prenta_Len = timer;
 // } 
}




void loop(){
Signal_change();
}





