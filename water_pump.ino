const int pumpPin =  11;   // initialize digital pin 9 for pump control

void setup() {
  // initialize the pump pin as an output:
  pinMode(pumpPin, OUTPUT);
}

void loop() {
    digitalWrite(pumpPin, HIGH);   // send signal from pin 9 to circuit
    delay(2000);                   // wait for 2 seconds
    digitalWrite(pumpPin, LOW);    // end signal
    delay(2000);                   // wait for 2 seconds before repeating loop
}