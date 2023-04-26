//#include <DFRobot_DHT11.h>

#include "dht.h"
#define dht_apin A1 // Analog Pin sensor is connected to Arduino
dht DHT;
#define POWER_PIN  7
#define SIGNAL_PIN A5
#define MQ2pin A2
#define PUMP_PIN A3

float gas_value=0.0;
int water_value = 0;
int fire_value=0; 
int water_level_flag=0;
float temperature = 0.0;
float humidity = 0.0;
bool is_fire=0;
int smoke_high=0;
bool watering=0;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
    
    lcd.begin(16, 2);
    Serial.begin(9600);
    delay(20000);
    pinMode(2, INPUT); //initialize Flame sensor output pin connected pin as input.
    pinMode(LED_BUILTIN, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
    pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(POWER_PIN, LOW);
    

}

int check_smoke(){
  if(gas_value>600){
    smoke_high=1;
    Serial.println("Gas too high. Avoid human intervention");

  }
  else if (200<gas_value<600){
    smoke_high=2;
    Serial.println("Gas manageable, fire nearby");
  }
  else if(gas_value<200){
    smoke_high=3;
    Serial.println("Gas is not a danger");
  }
  else{
    smoke_high=0;
  }
  return smoke_high;
}

int check_water(){
  if(water_value<300){
    //Serial.println("Water level too low, refill water");
    water_level_flag=0;

  }
  else{
    //Serial.println("Water level is okay, you can water");
    water_level_flag=1;
  }
  return water_level_flag;
}
bool start_water(){
  if(is_fire==1 && water_level_flag==1)
  {
    Serial.println("Fire detected, have enough water, initiating watering");
    digitalWrite(PUMP_PIN, HIGH);   // send signal from pin 9 to circuit
    watering=1;
  }
  else if (is_fire==1 && water_level_flag==0)
  {
    Serial.println("Fire detected, but cannot water, paani de do");
    //Add led indicator logic
    digitalWrite(PUMP_PIN,LOW);
    watering=0;
  }
  else{
    Serial.println("No watering required");
    digitalWrite(PUMP_PIN,LOW);
    watering=0;
  }
}
bool check_fire(){
if(fire_value==0 && temperature >= 25 && smoke_high==1){
  is_fire=1;
  Serial.println("Presence of Fire is 100% Confirmed & smoke is too high, humans should not enter");

}
else if(fire_value==0 && temperature < 25 &&  smoke_high==2){
  is_fire=1;
  Serial.println("Presence of Fire Confirmed and Temp of Area increasing and smoke is manageable");
}
else if(fire_value==1 && 15<temperature < 20 && smoke_high==2){
  is_fire=0;
  Serial.println("There could be fire in the proximity,some smoke is detected");
}
else if(fire_value==1 && temperature >= 25 && smoke_high>=2){
  is_fire=0;
  Serial.println("Temperature is high, there is a possibility of fire");
}
else if (fire_value==1 && temperature>=25 && smoke_high==1){
  is_fire=0;
  Serial.println("Fire has been extinguished but area is still dangerous");
}
else if(fire_value==0 && temperature>=25 && smoke_high==3){
  is_fire=1;
  Serial.println("Chemical fire , no smoke but fire present");
}
else if (fire_value==0 && temperature<20 && smoke_high==3){
  is_fire=1;
  Serial.println("Area has just caught fire");
}
else {
  is_fire=0;
  Serial.println("No fire detected");
}
return is_fire;
}
void loop() {
  
  lcd.setCursor(0, 0);
  DHT.read11(dht_apin);
  temperature= DHT.temperature;
  humidity = DHT.humidity;
  lcd.print("Humidity= ");
  lcd.print(DHT.humidity);
  lcd.print("%  ");
  lcd.setCursor(0, 1);
  lcd.print("Temp= ");
  lcd.print(DHT.temperature); 
  lcd.print("C  ");  
  delay(500);
  lcd.clear();
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  water_value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  //Serial.print("Sensor value: ");
  //Serial.println(water_value);
  delay(1000);
  fire_value=digitalRead(2);
  // fire_value=0;
  gas_value = analogRead(MQ2pin);
  
  // delay(500);
  // lcd.setCursor(0,0);
  // lcd.print("Smoke Val= ");  
  // lcd.print(gas_value);
  // lcd.setCursor(0,1);
  // lcd.print("Water Val= ");  
  // lcd.print(water_value); 
  // lcd.clear();      
  // Serial.println(gas_value);
  // Serial.println(water_value);
  // Serial.println(humidity);
  check_smoke();
  check_fire();
  check_water();
  start_water();
  
  Serial.println(gas_value);
  Serial.println(water_value);
  Serial.println(humidity);
  Serial.println(temperature);  
  Serial.println(is_fire);
  Serial.println(watering);
  delay(2000);


  
}