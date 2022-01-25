#include <DHT.h>

#define DHTPIN D13     // D5, Digital pin connected to the DHT sensor
//#define dht_GND D4     // Digital pin connected to the DHT sensor GND
//#define dht_POWER D6     // Digital pin connected to the DHT sensor POWER


// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)



void dht_init();
void oled_print_dht();
void dht_loop();
