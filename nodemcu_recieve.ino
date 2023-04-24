void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
if (Serial.available()) {
Serial.println(Serial.read());
delay(1000);
}
}



///Ignore



// #include <SoftwareSerial.h>

// // SoftwareSerial mySerial(5, 6); // RX, TX pins for SoftwareSerial communication with Arduino

// void setup() {
//   Serial.begin(115200); // NodeMCU serial monitor
//   // mySerial.begin(9600); // SoftwareSerial communication with Arduino
// }

// void loop() {
//   if (Serial.available()) {
//     String receivedData = Serial.readStringUntil('\n');
//     Serial.println("Received data from Arduino: " + receivedData);
//   }
// }