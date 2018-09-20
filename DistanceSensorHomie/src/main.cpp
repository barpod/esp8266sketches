#include <Homie.h>

const int DISTANCE_INTERVAL = 2;
unsigned long lastDistanceSent = 0;

HomieNode distanceNode("distance", "distance");

// defines pins numbers
const int trigPin = 4;  //D4
const int echoPin = 5;  //D3

// defines variables
long duration;
int distance;

void setupHandler() {
    //Serial.println("Setting up trigger pin.");
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    //Serial.println("Setting up echo pin.");
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loopHandler() {
   if (millis() - lastDistanceSent >= DISTANCE_INTERVAL * 1000UL || lastDistanceSent == 0) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(12);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance= duration*0.034/2;
    // distance= 20;
    // Prints the distance on the Serial Monitor
    // Serial.print("Distance: ");
    // Serial.println(distance);
    //Homie.getLogger() << "Distance:: " << distance << " cm" << endl;
    Serial.println("Before sending distance.");
    Serial.println(distance);
    distanceNode.setProperty("distance").send(String(distance));
    lastDistanceSent = millis();
     //Serial.println("Hello world");
   }
}

void setup() {
  Serial.begin(74880);
  Serial.println();
  Serial.println();
  Homie_setFirmware("test", "1.0.0");
  Homie.setLedPin(16, false);
  Homie.disableResetTrigger();
  Homie.disableLedFeedback();
  Serial.println("Before setSetupFunction.");
  Homie.setSetupFunction(setupHandler);
  Serial.println("Before setLoopFunction.");
  Homie.setLoopFunction(loopHandler);
  Serial.println("Before setup.");
  Homie.setup();
  Serial.println("After setup.");
}

void loop() {
  Homie.loop();
}