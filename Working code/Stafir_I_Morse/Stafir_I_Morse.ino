// morse-decode-encode for ESP32
#include "Arduino.h"

// Pin Definitions for ESP32
const int tonePin = 33;  // Change to appropriate pin for your setup
const int ledPin = 35;     // Change to appropriate pin for your setup
const int buttonPin = 32;  // Change to appropriate pin for your setup
const int debounceDelay = 30;

const int dotLength = 240; 
const int dotSpace = dotLength;
const int dashLength = dotLength * 3;
const int letterSpace = dotLength * 3;
const int wordSpace = dotLength * 7; 

int t1, t2, onTime, gap;
bool newLetter, newWord, letterFound, keyboardText;
int lineLength = 0;
const int maxLineLength = 20; 

const char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

const char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", //0-4
  ".....", "-....", "--...", "---..", "----." //5-9
};

String dashSeq = "";
char keyLetter, ch;
int i;

void setup() {
  delay(500);
  pinMode(ledPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println();
  Serial.println("-------------------------------");
  Serial.println("Morse Code decoder/encoder");
  Serial.println("-------------------------------");
      
  newLetter = false; 
  newWord = false;  
  keyboardText = false; 
}

void loop() {
  if (Serial.available() > 0) {
    if (keyboardText == false) {
      Serial.println();
      Serial.println("-------------------------------");
    }
    keyboardText = true;
    ch = Serial.read();
    if (ch >= 'a' && ch <= 'z') {
      ch = ch - 32;
    }

    if (ch >= 'A' && ch <= 'Z') {
      Serial.print(ch); 
      Serial.print(" ");
      Serial.println(letters[ch-'A']);
      flashSequence(letters[ch-'A']);
      delay(letterSpace);
    }
    if (ch >= '0' && ch <= '9') {
      Serial.print(ch);
      Serial.print(" ");
      Serial.println(numbers[ch-'0']);
      flashSequence(numbers[ch-'0']);
      delay(letterSpace);
    }
    if (ch == ' ') {
      Serial.println("_");
      delay(wordSpace);    
    } 

    if (Serial.available() <= 0) {
      Serial.println();
      Serial.println("Enter text or Key in:");
      Serial.println("-------------------------------");
      keyboardText = false;
    }
  }
 
  if (digitalRead(buttonPin) == LOW ) {
    newLetter = true; 
    newWord = true;
    t1 = millis(); 
    digitalWrite(ledPin, HIGH); 
    tone(tonePin, 1000); // You may need to adjust frequency
    delay(debounceDelay);     
    while (digitalRead(buttonPin) == LOW ) { 
      delay(debounceDelay);
    }
    delay(debounceDelay);
       
    t2 = millis();  
    onTime = t2 - t1;  
    digitalWrite(ledPin, LOW); 
    noTone(tonePin); 
    
    if (onTime <= dotLength * 1.5) { 
      dashSeq = dashSeq + ".";
    } else { 
      dashSeq = dashSeq + "-";
    }
  } 
  
  gap = millis() - t2; 
  if (newLetter == true && gap >= letterSpace) { 
    letterFound = false; 
    keyLetter = '?'; 
    for (i = 0; i <= 25; i++) {
      if (dashSeq == letters[i]) {
        keyLetter = i + 65;
        letterFound = true;   
        break;  
      }
    }
    if (letterFound == false) {
      for (i = 0; i <= 10; i++) {
        if (dashSeq == numbers[i]) {
          keyLetter = i + 48;
          letterFound = true;   
          break; 
        }
      }
    }    
    Serial.print(keyLetter);
    if (letterFound == false) {
      tone(tonePin, 100, 500);
    }  
    newLetter = false; 
    dashSeq = "";
    lineLength++;
  }  

  if (newWord == true && gap >= wordSpace * 1.5) { 
    newWord = false; 
    Serial.print("_");  
    lineLength++;
    digitalWrite(ledPin, HIGH);
    delay(25);
    digitalWrite(ledPin, LOW);       
  } 

  if (lineLength >= maxLineLength) {
    Serial.println();
    lineLength = 0;
  }      
} 

void flashSequence(const char* sequence) {
  int i = 0;
  while (sequence[i] == '.' || sequence[i] == '-') {
    flashDotOrDash(sequence[i]);
    i++;
  }
}

void flashDotOrDash(char dotOrDash) {
  digitalWrite(ledPin, HIGH);
  tone(tonePin, 1000); // You may need to adjust frequency
  if (dotOrDash == '.') {
    delay(dotLength);
  } else {
    delay(dashLength);
  }
  digitalWrite(ledPin, LOW);
  noTone(tonePin);
  delay(dotLength); 
}