#include <DFRobot_DHT11.h>

#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to Arduino
dht DHT;
#define POWER_PIN  7
#define SIGNAL_PIN A5

int water_value = 0;
int fire_value=0;
int water_level_flag=0;
float temperature = 0.0;
float humidity = 0.0;
bool is_fire=0;

void setup() {
    pinMode(2, INPUT); //initialize Flame sensor output pin connected pin as input.
    pinMode(LED_BUILTIN, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
    pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
    digitalWrite(POWER_PIN, LOW);
    Serial.begin(9600);// initialize serial communication @ 9600 baud:

}

int check_water(){
  if(water_value<40){
    Serial.println("Water level too low, you cannot water");
    water_level_flag=0;

  }
  else{
    Serial.println("Water level is okay, you can water");
    water_level_flag=1;
  }
  return water_level_flag;
}
void start_water(){
  if(is_fire==1 && water_level_flag==1)
  {
    Serial.println("Fire detected, have enough water, initiating watering");
    //Add motor logic
  }
  else if (is_fire==1 && water_level_flag==0)
  {
    Serial.println("Fire detected, but cannot water, paani de do");
    //Add led indicator logic
  }
  else{
    Serial.println("No fire, sab chill karo");
  }
}
bool check_fire(){
if(fire_value==0 && temperature > 25){
  is_fire=1;
  Serial.println("Presence of Fire is 100% Confirmed");

}
else if(fire_value==0 && temperature < 25){
  is_fire=1;
  Serial.println("Presence of Fire Confirmed and Temp of Area increasing");
}
else if(fire_value==1 && 15<temperature < 20){
  is_fire=0;
  Serial.println("There could be fire in the proximity");
}
else{
  is_fire=0;
  Serial.println("There is no fire");
}
return is_fire;
}
void loop() {

  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  water_value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  //Serial.print("Sensor value: ");
  //Serial.println(water_value);
  delay(1000);
  //fire_value=digitalRead(2);
  fire_value=0;
  DHT.read11(dht_apin);
  temperature= DHT.temperature; 
  humidity = DHT.humidity;
  check_water();
  check_fire();
  start_water();
  delay(2000);

}
