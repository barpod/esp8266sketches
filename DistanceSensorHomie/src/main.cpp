#include <Homie.h>

const int DISTANCE_INTERVAL = 2;
unsigned long lastDistanceSent = 0;

HomieNode distanceNode("distance", "distance");

// defines pins numbers
const int trigPin = 4;  //D2
const int echoPin = 5;  //D1

// defines variables
long duration;
int distance;

void setupHandler() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
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
    Serial.println("Before sending distance.");
    Serial.println(distance);
    distanceNode.setProperty("distance").send(String(distance));
    lastDistanceSent = millis();
   }
}

void setup() {
  Serial.begin(74880);
  Serial.println();
  Serial.println();
  Homie_setFirmware("distance-sensor", "1.0.0");
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