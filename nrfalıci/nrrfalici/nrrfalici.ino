#include <SPI.h>
#include <nRF24L01p.h>
  
nRF24L01p alici(6,5);//CSN,CE
  
void setup(){
 delay(150);
 Serial.begin(115200);
 SPI.begin();
 SPI.setBitOrder(MSBFIRST);
 alici.channel(90);
 alici.RXaddress("kontrol");
 alici.init();
}
  
String message;
  
void loop(){ 
 if(alici.available()){
 alici.read();
 alici.rxPL(message);
 Serial.println(message);
 message="";
 }
}
