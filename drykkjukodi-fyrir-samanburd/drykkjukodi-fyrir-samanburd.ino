/* Replace these values with your own readings */
#define Sober 2500   // Define max value that we consider sober
#define Drunk 3000   // Define min value that we consider drunk

#define MQ3pin 34
#define Outpin 25

float sensorValue;  //variable to store sensor value

void setup() {
  Serial.begin(115200); // sets the serial port to 9600
  Serial.println("MQ3 warming up!");
  pinMode(Outpin, OUTPUT);    // sets the digital pin 13 as output
  digitalWrite(Outpin, LOW);
  delay(20000); // allow the MQ3 to warm up
}

void loop() {
  sensorValue = analogRead(MQ3pin); // read analog input pin 0

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  
  // Determine the status
  if (sensorValue < Sober) {
    Serial.println("  |  Status: Stone Cold Sober");
    digitalWrite(Outpin, LOW);
  } else if (sensorValue >= Sober && sensorValue < Drunk) {
    Serial.println("  |  Status: Drinking but within legal limits");
    digitalWrite(Outpin, LOW);
  } else {
    Serial.println("  |  Status: DRUNK");
    digitalWrite(Outpin, HIGH);
  }
  
  delay(200); // wait 2s for next reading
}
