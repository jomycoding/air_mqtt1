#include "jm_dht.h"
#include "jm_global_data.h"
#include "jm_config.h"


DHT dht(DHTPIN, DHTTYPE);



void dht_init(){
  dht.begin();
//  pinMode(dht_GND,OUTPUT);
//  digitalWrite(dht_GND,LOW);
  
//  pinMode(dht_POWER,OUTPUT);
//  digitalWrite(dht_POWER,HIGH);

  // Wait a few seconds between measurements.
  delay(2000);
}




void dht_loop() {
  // Wait a few seconds between measurements.
  //delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.println("***********************");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  Serial.println("***********************");

  //temperature modification 

  dht_te_modi = t + Delta_TE;
  dht_hu_modi = h + Delta_HU;
    
}
