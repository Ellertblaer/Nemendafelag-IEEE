//setup á skjá
#include <Wire.h>
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  


#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Initialize the SSD1306 display with the I2C address 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//tenging á skjánum er svona
//Setup:
//ESP32 -    Skjár
//GND   -    GND
//V5    -    VCC
//G21   -    SDA
//G22   -    SCL



//tími tölvunar þegar ýtt er á takkan
int pressTime = 0;
//tími þegar ekkert input er gert
int notTime = 0;
// passar að það sé ekki að fokkast upp þegar timePressed() runnar þegar það er ekki ýtt
int tempTime = 0;
//tími tölvunar þegar takkanum er sleppt
int releaseTime = 0;
// tíminn sem takkanum var haldið niðri
int totalTime = 0;

String geymsla = "";
String stafur = "";

const int Button = 32;
const int Pressed = 33;

//Setur upp strúktur fyrir fylkið að neðan
struct MorseCodeSignal {
  String Letter;
  String Signal;
};


MorseCodeSignal MorseCode[26] = {
  { "A", ".-" }, { "B", "-..." }, { "C", "-.-." }, { "D", "-.." }, { "E", "." },
  { "F", "..-." }, { "G", "--." }, { "H", "...." }, { "I", ".." }, { "J", ".---" },
  { "K", "-.-" }, { "L", ".-.." }, { "M", "--" }, { "N", "-." }, { "O", "---" },
  { "P", ".--." }, { "Q", "--.-" }, { "R", ".-." }, { "S", "..." }, { "T", "-" },
  { "U", "..-" }, { "V", "...-" }, { "W", ".--" }, { "X", "-..-" }, { "Y", "-.--" }, { "Z", "--.." }
};


void setup() {

  Serial.begin(115200);

  pinMode(Button, OUTPUT);
  pinMode(Pressed, INPUT);
  digitalWrite(Button, HIGH);
}
//skoðar hversu lengi takkanum var haldið inni
//PASSA: if-setning virkar ekki á digitalRead(Pressed) því það mun alltaf vera satt (veit ekki afhverju)
void timePressed() {
  pressTime = millis();

  while (digitalRead(Pressed)) {
  }
  tempTime = millis();
  if(tempTime-pressTime>15){
    releaseTime = tempTime;
    totalTime = releaseTime - pressTime;
  }
  
}

void findLetter() {

  for (int i = 0; i < 26; i++) {
    if (MorseCode[i].Signal == geymsla) stafur = MorseCode[i].Letter;
  }
}

void loop() {
    
    timePressed();

  notTime=millis();
  if (totalTime > 20 && totalTime < 200) {
    Serial.print(". ");
    geymsla += ".";
    totalTime = 0;
  }
  if (totalTime > 200) {
    Serial.print("- ");
    geymsla += "-";
    totalTime = 0;
  }
  //ef það er ekkert input í 500 ms leitar hann af staf
  if(notTime-releaseTime>500){
    findLetter();
  }
  // ef stafur hefur verið fundinn  prentar hann stafin og hreinsar geymslur
  if (stafur != "") {
    //Hreinsa skjá
    display.clearDisplay(); //hreinsar alltaf skjáinn í hvert sinn. Þið getið líka fært þetta í að það hreinsist þegar við erum búin að skirfa orðið. Eða ýtt er á einhvern annan takka.
    display.setTextColor(SSD1306_WHITE); //þetta er bara liturinn á stafnum
    display.setTextSize(5); //Stærð á texta hægt að breyta
    display.setCursor(0, 0);
    display.print(stafur); //prentar staf á skjá
    
    
    //tæmir geymslu
    geymsla = "";
    stafur = "";
  }
}
