#include "jm_pms7003_nodemcu.h"
#include "jm_global_data.h"
#include "jm_config.h"

////////////////////////////////////////

//
// Please uncomment #define PMS_DYNAMIC in pmsConfig.h file
//

#if defined PMS_DYNAMIC
Pmsx003 *pms_ = nullptr;
#define pms (*pms_)
#else
Pmsx003 pms(D7, D8);  //D7 rx, D8 tx, maybe swserial.
#endif

////////////////////////////////////////



void pms7003_nodemcu_init(void) {
  Serial.begin(115200);
  while (!Serial) {};
  Serial.println("Pmsx003");

#if defined PMS_DYNAMIC
  pms_ = new Pmsx003(D7, D8);
#else
  pms.begin();
#endif 

  pms.waitForData(Pmsx003::wakeupTime);
  pms.write(Pmsx003::cmdModeActive);
}


auto lastRead = millis();

int pms7003_loop(void) {    //PMS25 raw data
  
  const Pmsx003::pmsIdx n = Pmsx003::nValues_PmsDataNames;
  Pmsx003::pmsData data[n];

  auto t0Read = millis();
  Pmsx003::PmsStatus status = pms.read(data, n);
  auto t1Read = millis();

  switch (status) {
    case Pmsx003::OK:
    {
      Serial.print("_________________ time of read(): ");
      Serial.print(t1Read - t0Read);
      Serial.println(" msec");
      auto newRead = millis();
      Serial.print("Wait time ");
      Serial.println(newRead - lastRead);
      lastRead = newRead;

      for (Pmsx003::pmsIdx i = 0; i < n; ++i) {

        //Serial.println("_________________");
        //Serial.print(status);
        //Serial.print(" status : ");
        //Serial.println(Pmsx003::errorMsg[status]);
        
        Serial.print(i);
        Serial.print(": ");
        Serial.print(data[i]);
        Serial.print("\t");
        Serial.print(Pmsx003::getDataNames(i));
        Serial.print(" [");
        Serial.print(Pmsx003::getMetrics(i));
        Serial.print("]");
        Serial.println();
        
      }
      
      return data[1]; //jm    
      break;
    }
    case Pmsx003::noData:
      return 0;
      break;
      
    default:
      Serial.println("_________________");
      Serial.print(status);
      Serial.print(" status : ");
      Serial.println(Pmsx003::errorMsg[status]);

      return 0;
  }

}

void pms7003_nodemcu_PM25mean(void) {  //PMS7003 메인함수 pm25평균값 구하기, oled 호출
  
  int PM25_now=0.0;
  int PM25_sum=0.0;
  int PM25_mean=0.0;  
  int n_eff=0;
  
  for(int i=0; i<NUM_SAMPLE; i++){ 
    
    PM25_now = pms7003_loop(); 
    Serial.println("***************");
    Serial.print(i);
    Serial.print("(i): PM25_now =");
    Serial.println(PM25_now);  
    
    PM25_sum= PM25_sum + PM25_now;
    if(PM25_now == 0) i=i-1 ;
    n_eff = i+1;
    delay(1000);
  }
  
  PM25_mean = PM25_sum/n_eff;
  pm25=PM25_mean; //jm global변수에 저장

  
  Serial.print(n_eff);
  Serial.print("(neff): PM25_sum =");
  Serial.print(PM25_sum); 
  Serial.print(": PM25_mean =");
  Serial.println(PM25_mean); 

  //oled_print(PM25_mean); 
}
