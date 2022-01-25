#include "jm_oled.h" 
#include "jm_global_data.h"
#include "jm_config.h"
#include "jm_func.h"
#include "jm_bitmap.h"

/* Create an instance for the SSD1306 OLED display in SPI mode 
 * connection scheme: 
 *   D0=sck=Pin 12  =SCL 
 *   D1=mosi=Pin 11 =SDA
 *   CS=Pin 3 or GND or NONE     =NONE (for 6 Pin oled)
 *   DC=A0=Pin 4    =DC
 *   Reset=Pin 5    =RST
 */


U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* cs=*/ U8X8_PIN_NONE, /* dc=*/ 2, /* reset=*/ 16 ); //성공 6pin
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 2, /* reset=*/ 16); //성공 7pin
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ U8X8_PIN_NONE); //성공


float dht_te_modi, dht_hu_modi;
int pm25;

void oled_init(){
  u8g2.begin();  
  u8g2.setContrast(0);
  u8g2.firstPage(); 
    do{       
      u8g2.setFont(u8g2_font_fub20_tr);   // for 2 color oled
      //u8g2.setFont(u8g2_font_unifont_t_korean1);  
      u8g2.drawStr(10,30,"Air&");
      u8g2.setFont(u8g2_font_fur11_tr);
      u8g2.drawStr(80,15,"PM2.5");
      u8g2.setFont(u8g2_font_fub20_tr);
      u8g2.drawStr(10,55,"Humidity");
    }while(u8g2.nextPage()); 
}


void oled_print_dht(){

    //String dst1 = digits3(t);
    //const char* cdst1=(const char*) dst1.c_str();
    //String dst2 = digits3(h);
    //const char* cdst2=(const char*) dst2.c_str();    
    
    char cdst3[10]; 
    dtostrf(dht_te_modi , 3, 1, cdst3);  // 5 : width, 2 : precision
    char cdst4[10]; 
    dtostrf(dht_hu_modi , 3, 0, cdst4);  // 5 : width, 2 : precision


    if(dht_hu_modi <= REF_HU_WARN){   
     for(int k=1; k<6; k++){   
      u8g2.firstPage(); 
      do{ 
        //void U8G2::drawBitmap(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t cnt, u8g2_uint_t h, const uint8_t *bitmap) 
        // cnt=width/8
        u8g2.drawBitmap(12,2,13,64,dry_104x64); 
        //u8g2.setFont(u8g2_font_fub20_tr);
        //u8g2.drawStr(20,30,"Very");
        //u8g2.drawStr(40,60,"Dry~!");  
      }while(u8g2.nextPage());
      delay(2000);
      
      u8g2.firstPage(); 
      do{  
        u8g2.drawBitmap(17,2,13,64,dry_104x64);
        //u8g2.setFont(u8g2_font_fub20_tr);
        //u8g2.drawStr(25,30,"Very");
        //u8g2.drawStr(50,60,"Dry~!");  
      }while(u8g2.nextPage());
      delay(2000);
     } 
      
    } //end of if(very dry)

    if((dht_hu_modi<= REF_HU) || (dht_hu_modi>= REF_HU_wet) ){   
     u8g2.firstPage(); 
     do{ 
      u8g2.setFont(u8g2_font_fur11_tr);
      u8g2.drawStr(70,12,cdst3); // top
      u8g2.drawStr(102,12,"`C");

      u8g2.setFont(u8g2_font_fub42_tn);
      u8g2.drawStr(17,62,cdst4); // body - humidity
      
      u8g2.setFont(u8g2_font_fub20_tr);
      u8g2.drawStr(102,62,"%");
       
     }while(u8g2.nextPage()); 
     delay(2000);
     
     if(dht_te_modi >= REF_TE) delay(13000); 
     //  temperature change, check below "if-sentence"
    }
   
        
  
   if(dht_te_modi >= REF_TE_WARN){      
     for(int k=1; k<6; k++){   
      u8g2.firstPage(); 
      do{ 
        //void U8G2::drawBitmap(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t cnt, u8g2_uint_t h, const uint8_t *bitmap) 
        // cnt=width/8
        u8g2.drawBitmap(12,2,13,64,hot_104x64); 
        //u8g2.setFont(u8g2_font_fub20_tr);
        //u8g2.drawStr(20,30,"Very");
        //u8g2.drawStr(40,60,"Hot~!");  
      }while(u8g2.nextPage());
      delay(2000);
      
      u8g2.firstPage(); 
      do{  
        u8g2.drawBitmap(17,2,13,64,hot_104x64); 
        //u8g2.setFont(u8g2_font_fub20_tr);
        //u8g2.drawStr(25,30,"Very");
        //u8g2.drawStr(50,60,"Hot~!");  
      }while(u8g2.nextPage());
      delay(2000);
     }   
   }  //end of if("very hot")

  if(dht_te_modi >= REF_TE){ 
     u8g2.firstPage(); 
     do{ 
      u8g2.setFont(u8g2_font_fur11_tr);
      u8g2.drawStr(8,12,cdst4); //  top
      u8g2.drawStr(35,12,"%");

      u8g2.setFont(u8g2_font_fub35_tn);
      u8g2.drawStr(6,60,cdst3); //  body - temperature
      
      //u8g2.drawBitmap(50,40,3,40,percent_24x40);  
      u8g2.setFont(u8g2_font_fur11_tr);
      u8g2.drawStr(110,40,"`C");
       
     }while(u8g2.nextPage()); 
     delay(2000);
     //delay(13000); delay time of PMS7003
  }

}


void oled_print_pm25(){
   int pm2_5_mean=pm25;
  
   if(pm2_5_mean > REF_PM25_WARN){
   for(int k=1; k<6; k++){
    u8g2.firstPage(); 
    do{ 
        u8g2.drawBitmap(12,2,13,64,dust_104x64); 
        //u8g2.setFont(u8g2_font_fub20_tr);
        //u8g2.drawStr(20,30,"Bad");
        //u8g2.drawStr(40,60,"Air!");
    }while(u8g2.nextPage());     
    delay(2000);
    
    u8g2.firstPage(); 
    do{ 
        u8g2.drawBitmap(17,2,13,64,dust_104x64); 
        //u8g2.setFont(u8g2_font_fub20_tr);
        //u8g2.drawStr(25,30,"Bad");
        //u8g2.drawStr(60,60,"Air!");
    }while(u8g2.nextPage());     
    delay(2000);    
   }
  }
  
  u8g2.firstPage();
  do{
        // temperature & humidity from DHT----------------------------
        char cdst11[10]; 
        dtostrf(dht_te_modi , 3, 1, cdst11);  // 5 : width, 2 : precision
        char cdst12[10]; 
        dtostrf(dht_hu_modi , 3, 0, cdst12);  // 5 : width, 2 : precision

        u8g2.setFont(u8g2_font_fur11_tr);
        u8g2.drawStr(70,12,cdst11); 
        //u8g2.setPrintPos(70,12);
        //u8g2.print(dht_te_modi);        
        u8g2.drawStr(102,12,"`C");
                
        u8g2.drawStr(8,12,cdst12); 
        //u8g2.setPrintPos(8,12);
        //u8g2.print(dht_hu_modi);
        u8g2.drawStr(35,12,"%");
        // end of DHT ---------------------------------------------
  
        
        String dst2 = digits3(pm2_5_mean);
        const char* cdst2=(const char*) dst2.c_str();
        u8g2.setFont(u8g2_font_fur11_tr);
        u8g2.drawStr(112,57,"ug");      
        u8g2.setFont(u8g2_font_fub42_tn);
        u8g2.drawStr(11,62,cdst2); //  body    
             
   }while (u8g2.nextPage());
   delay(15000); 
}
