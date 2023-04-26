// plant_watering_Lab2
// For ESE515 2022


#include "config.h"

#include "DHT.h"

#define DHT_SENSOR_TYPE DHT11 //notice our sensor number here
#define DHT_SENSOR_PIN A0 // assign name of variable and pin number
DHT dht( DHT_SENSOR_PIN, DHT_SENSOR_TYPE ); //command specific to library

// set up the 'soil_moisture', 'temperatureDHT' and 'humidityDHT' feeds
// AdafruitIO_Feed *soil_moisture  = io.feed("soil_moisture");
AdafruitIO_Feed *temperatureNEW = aio.feed("temperatureNEW");
AdafruitIO_Feed *humidityNEW = aio.feed("humidityNEW");
// AdafruitIO_Feed *IsPlantWatered = io.feed("IsPlantWatered");
//AdafruitIO_Feed *temperatureThermistor = io.feed("temperatureThermistor");

// these correspond to the pins on your NodeMCU
// #define pumpPin D2    //D2 in Node MCU to drive watering pump
// #define threshold 700 //after tinkering with your moisture sensor, feel free to change 'threshold' to a desired value

// int sm = 0;
float temperature = 0; //float variables allow for decimals
float humidity = 0;

// int ThermistorPin = 0;
// int Vo;
// float R1 = 10000;
// float logR2, R2, T, Tc, Tf;
// float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;

// void send_thermistor_Sensor() {

//   Vo = analogRead(ThermistorPin);
//   R2 = R1 * (1023.0 / (float)Vo - 1.0);
//   logR2 = log(R2);
//   T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
//   Tc = T - 273.15;
//   Tf = (Tc * 9.0)/ 5.0 + 32.0; 

//   temperatureThermistor->save(Tc);
//   delay(500);
// }

// void send_sm_Sensor()
// {
//   sm = analogRead(A0); //input from soil moisture sensor

//   soil_moisture->save(sm);
//   delay(2000);
// }


void send_dht_Sensor()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    humidity = dht.readHumidity();
    // Read temperature as Celsius (the default)
    temperature = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
      delay(1000);
      }
    else {
      temperatureNEW->save(temperature);
      delay(2000);
      humidityNEW->save(humidity);
      delay(2000);
    }   
 
}

// void water_plant ()
// {
//   int plantWater;
//   if(sm < threshold) //this means soil is wet and doesn't need to be watered
//   {
//     digitalWrite (pumpPin , LOW);
//     plantWater = 0; 
//     IsPlantWatered->save(plantWater);
//     delay(3000);
//   }
//   else
//   {
//     digitalWrite (pumpPin , HIGH);
//     plantWater = 100;
//     IsPlantWatered->save(plantWater);    
//     delay(3000);
//     digitalWrite (pumpPin, LOW); //prevent pump from staying on
//   }
// }

void setup() {
  // declare pins as inputs and outputs
  // pinMode (pumpPin, OUTPUT );
   
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  aio.connect();

  // wait for a connection
  while(aio.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(aio.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  aio.run();

  // send soil moisture data
  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. 
  // send_sm_Sensor();
  // // send_thermistor_Sensor();
  // delay(2000);
  send_dht_Sensor();
  delay(2000);

  // water_plant(); 
}
