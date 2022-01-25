#include "jm_oled.h"
#include "jm_dht.h"
#include "jm_pms7003_nodemcu.h"
#include "jm_mqtt.h"


void setup() {
  Serial.begin(115200);
  Wire.begin(); 

  oled_init();
  mqtt_init();  
  dht_init();    
  pms7003_nodemcu_init();  
   
}


void loop() {
  
  dht_loop(); 
  oled_print_dht(); 
  pms7003_nodemcu_PM25mean();
  oled_print_pm25(); 
  mqtt_loop();
  
}
