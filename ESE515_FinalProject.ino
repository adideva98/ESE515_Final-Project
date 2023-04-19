#define POWER_PIN  7
#define SIGNAL_PIN A5

int water_value = 0;
int fire_value=0;
int water_level_flag=0;

void setup() {
    pinMode(2, INPUT); //initialize Flame sensor output pin connected pin as input.
    pinMode(LED_BUILTIN, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
    pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
    digitalWrite(POWER_PIN, LOW);
    Serial.begin(9600);// initialize serial communication @ 9600 baud:

}

int check_water(){
  if(water_value<40){
    Serial.println("Water level, too low cannot water");
    water_level_flag=0;

  }
  else{
    Serial.println("Water level is okay, you can water");
    water_level_flag=1;
  }
  return water_level_flag;
}
void check_fire(){
  if(fire_value==0 && water_level_flag==1)
  {
    Serial.println("Fire detected, have enough water, initiating watering");
    //Add motor logic
  }
  else if (fire_value ==0 && water_level_flag==0)
  {
    Serial.println("Fire detected, but cannot water, paani de do");
    //Add led indicator logic
  }
  else{
    Serial.println("No fire, sab chill karo");
  }
}
void loop() {

  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  water_value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  Serial.print("Sensor value: ");
  Serial.println(water_value);
  delay(1000);
  fire_value=digitalRead(2);
  check_water();
  check_fire();
  delay(100);

}
