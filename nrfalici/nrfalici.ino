/////////UNO ALICI/////////////////////////////////////////////////
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <Timer.h>
#define panelno 1
/////////////////////////////////////////////////////////////////
unsigned long timer;
SoftDMD dmd(1,1);  // DMD controls the entire display
DMD_TextBox box(dmd, 0, 2); 
RF24 radio(10, 5); // radio(CE, CS);
const uint64_t kod = 0xE8E8F0F0E1LL;
int sayi[6];//gönderilen degerler
int ssw;
int sayi3=0;//sayılacak deger
int say=0;//buton
////////////////////////////////////////////////////////////////
void timeyaz()
{        
       while (sayi3>0)
           {
              radio.read(sayi, sizeof(sayi));
              say=sayi[0];//butona basıldıysa 1 olacak
              Serial.print("gelen:");
              Serial.println(sayi[panelno]);
              if(sayi[panelno]>0)sayi3=sayi[panelno];//yeni deger geldiyse eşitle
              while (say==1)
              {                
                timer = millis();//sayaç başlat                
                int mod =timer%1000;//sn ayarlama
                if(mod==0)//syaç başla
                  {
                    radio.read(sayi, sizeof(sayi));
                    sayi3-=1;
                    box.clear();
                    box.print(sayi3);//panele yaz
                    Serial.println(sayi3);
                    if(sayi3==0)//- degere inmememsi için
                      {                        
                        say=0;break;
                      }
                  }
             }                  
          } 
  if (sayi[panelno]==0)
    {
      box.println(0);  
    }                 
}
/////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, kod);
  radio.startListening();
  dmd.setBrightness(255);
  dmd.selectFont(Arial14);
  dmd.begin();  
}
/////////////////////////////////////////////////////////////////////////
void loop()
{ 
  if (radio.available())
    {
        box.print(0);        
        while (1)
          { 
            radio.read(sayi, sizeof(sayi));//gönderilen degerleri alma
            sayi3=sayi[panelno];//sayılacak degeri secme
            delay(100);               
            Serial.println(sayi3);  
            /*for(int i=0;i<4;i++)
                {
                  Serial.print("sayi[i]:");Serial.println(sayi[i]);
                }  */               
            timeyaz();     
          }    
    }
}

