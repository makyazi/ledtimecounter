/////////UNO ALICI/////////////////////////////////////////////////
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <Timer.h>
#define panelno 1
#include "Countimer.h"
/////////////////////////////////////////////////////////////////
Timer t;
Countimer tDown;
Timer t2;
Timer t3;
unsigned long timer;
unsigned long timer2=0;
SoftDMD dmd(3,1);  
SoftDMD dmd1(3,1);
SoftDMD dmd2(3,1);
DMD_TextBox box(dmd, 6, 2);  
DMD_TextBox box1(dmd1, 38, 2); 
DMD_TextBox box2(dmd2, 70, 2);
RF24 radio(10, 5); // radio(CE, CS);
const uint64_t kod = 0xE8E8F0F0E1LL;
int sayi[7];//gönderilen degerler
int ssw;
int sayi3=0;//sayılacak deger
int sayi33=0;
int say1=0;
int say=0;//buton
int sayiman1=0;
int sayiman=0;
////////////////////////////////////////////////////////////////
void al()
{
    
          radio.read(sayi, sizeof(sayi));
          Serial.println(sayi[0]);


              if(sayi[panelno]>0||sayi[panelno+1]>0)
                { 
                  sayi33=sayi[panelno];//yeni deger geldiyse eşitle
                  sayiman1=sayi[panelno+1];                                
                }      
           
          switch (sayi[0])
            {
                case 1:   say=1;break;
                case 2:   say1=2;break;
                                                                               
            }
         //timer =millis();Serial.print("timer2:");Serial.print(timer);
        
}
////////////////////////////////////////////////////////////////
void fonk1()
{
  
  if (sayiman==0)
      {
        say1=0;
        sayiman=sayiman1;
      }
  else
   {
       sayiman-=1;
       box1.clear();
       box1.print(sayiman);//panele ya
   }
  
  
}
////////////////////////////////////////////////////////////////
void fonk2()
{
  
  if (sayi3==0)
     { 
      say=0;
      sayi3=sayi33;
     }
  else
  {    
  sayi3-=1;
  box.clear();
  box.print(sayi3);//panele yaz 
  }
  
}
////////////////////////////////////////////////////////////////
void timeyaz()
{        
       while (sayi3>0||sayiman>0)
           {
               if (radio.available())
                  {
                    radio.read(sayi, sizeof(sayi));
                    say=sayi[0];//butona basıldıysa 1 olacak
                    say1=sayi[0];
                    Serial.print("gelen:");
                    Serial.println(sayi[panelno]);
                    Serial.println(sayi[panelno+1]);
                  }
              if(sayi[panelno]>0||sayi[panelno+1]>0)
              {
 
                sayi3=sayi[panelno];//yeni deger geldiyse eşitle
                sayiman=sayi[panelno+1];
                
                
              }
              while (say==1||say1==2)
              {     
                    
                    t3.update();
                    
                    while (say1==2)
                    { 
                      t.update();
                      t3.update();break;   
                    }
                    
                    while (say==1)
                    {
                      t2.update();  
                      t3.update();break;               
                    }                                                                                                        

                    
             }
          }
             /*while (say1==2)
              {                
                timer = millis();//sayaç başlat                
                int mod =timer%1000;//sn ayarlama
                if(mod==0)//syaç başla
                  {
                    radio.read(sayi, sizeof(sayi));
                    if(sayi[panelno]>0)
                      {
                        say=sayi[0];
                        sayi3=sayi[panelno];//yeni deger geldiyse eşitle                        
                      }                     
                    sayiman-=1;
                    
                    box1.print(sayiman);//panele yaz                   
                    Serial.println(sayiman);
                    if(sayiman==0)//- degere inmememsi için
                      {                        
                        say=0;break;
                      }
                  }
             }*/                  
           
  if (sayi3==0&&sayiman==0)
    {
      t3.update();     
      box.println(0);
      box1.println(0);
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
  dmd1.setBrightness(255);
  dmd1.selectFont(Arial14);
  dmd1.begin();
  t.every(640, fonk1);
  t2.every(640, fonk2);
  t3.every(1000, al); 
      // Count-down timer with 21s

     
}

/////////////////////////////////////////////////////////////////////////
void loop()
{ 
  if (radio.available())
    {

       dmd.fillScreen(true);
      delay(500);
      dmd.clearScreen();
      delay(500); 
        box.println(0);
        box1.println(0);       
        while (1)
          { 
            radio.read(sayi, sizeof(sayi));//gönderilen degerleri alma
            sayi3=sayi[panelno];//sayılacak degeri secme
            sayiman=sayi[panelno+1];
            say=sayi[0];
            say1=sayi[0];
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

