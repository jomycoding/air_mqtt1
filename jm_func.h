                                                                                                                                                                                                                                                 #include <Arduino.h>

String digits3(float f_number){
  
  if(f_number<0) f_number=0;
  String dst=String(int(f_number),DEC);
  if(f_number < 10) dst="00"+ dst;
  else if(f_number < 100) dst="0"+ dst;
    
  return dst;
}
    
