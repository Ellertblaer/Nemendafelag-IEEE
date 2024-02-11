const int ledPin = 32; // Onboard LED is connected to GPIO2
const int ledPin2 = 33; // Onboard LED is connected to GPIO2
void setup() {
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
  pinMode(ledPin2, INPUT); // Set the LED pin as an output
}
void loop() {
  if(digitalRead(ledPin2)){
  digitalWrite(ledPin, HIGH);
  } else{
  digitalWrite(ledPin, LOW);
  }
}