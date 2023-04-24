// #include "DHT.h"
// #include <SoftwareSerial.h>
// #define DHTPIN 2
// #define DHTTYPE DHT11 // DHT 11
// SoftwareSerial espSerial(5, 6);
// DHT dht(DHTPIN, DHTTYPE);
// String str;
void setup(){
Serial.begin(115200);
// espSerial.begin(115200);
// dht.begin();
delay(2000);
}
void loop()
{
float h = 25.0;

// float t = dht.readTemperature();
// Serial.print("H: ");
Serial.println("h");
// Serial.print("% ");
// Serial.print(" T: ");
// Serial.print(t);
// // Serial.println("C");
// str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);
// espSerial.println(str);
delay(1000);
}