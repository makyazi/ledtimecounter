#include <Wire.h>
//#include <DS1307new.h>
#include <LiquidCrystal.h>
#define KIRMIZI 1
#define YESIL   2


LiquidCrystal lcd(12, 11, 5, 4, 3, 2); /* LCDnin baglandigi Arduino pinleri */
const int buzzerPin= 0; 
const int ButonK = 7; /* Butonun bağlı olduğu pin */
const int ButonY = 6; /* Butonun bağlı olduğu pin */
const int LED_Kirmizi =1; /* LEDin bağlı olduğu pin */
const int LED_Yesil =13;

int ledDurumu=0;
int ButonDurumu = 0; /* Butonun durumu */  
int ButonDurumuY = 0; /* Butonun durumu */  
int LEDDurumuYesil = 0; /*  LED durumu */
int LEDDurumuKirmizi =0;
boolean LEDDurumuY = LOW;/*  LED durumu */
boolean LEDDurumuK= HIGH;
int Buzzer = 0;
uint8_t GUN=2;
int sure=0;
boolean BuzzerDurumu=LOW;
void KirmiziButon();
void YesilButon();
void KirmiziYesil();


void setup()
{
 // Serial.begin(9600);
  pinMode(ButonK, INPUT); /* Butonun pini giriş olarak ayarlandı */
  pinMode(ButonY, INPUT); /* Butonun pini giriş olarak ayarlandı */
  pinMode(LED_Kirmizi, OUTPUT);/* LED pini çıkış olarak ayarlandı */
  pinMode(LED_Yesil, OUTPUT);/* LED pini çıkış olarak ayarlandı */
  pinMode(buzzerPin,OUTPUT); /*Buzzer' ın bağlı olduğu pini  çıkış pin*/
  digitalWrite(LED_Yesil,LOW);
   digitalWrite(LED_Kirmizi,HIGH);
   digitalWrite(buzzerPin,HIGH);
  lcd.begin(16, 2); /* Kullandigimiz LCDnin sutun ve satir sayisini belirtmeliyiz */

}

void loop(){
  lcd.setCursor(0, 1);
//  lcd.print(RTC.getTime()); 

  
  switch (GUN)   // Haftanın günleri
  {
    case 1:          
    { 
      KirmiziButon();
      YesilButon();
      switch(ButonDurumu)
      {
        case KIRMIZI:
        { 
         if(LEDDurumuYesil=1)
         {
           digitalWrite(LED_Yesil,LOW);
           LEDDurumuYesil=0;
         } 
         digitalWrite(LED_Kirmizi,LOW);    
         for(sure=0;sure<5000;sure++)
         {
          delay(1);
          if(digitalRead(ButonY))
          {
           while(digitalRead(ButonY));
           digitalWrite(buzzerPin,LOW);
          }
         }
          digitalWrite(buzzerPin,HIGH);
          digitalWrite(LED_Kirmizi,HIGH);
          ButonDurumu=0;  
        }
          break;

          case YESIL:
          {
            LEDDurumuY=!LEDDurumuY;
            digitalWrite(LED_Yesil,LEDDurumuY);
            ButonDurumu=0;
            if(digitalRead(LED_Yesil)==HIGH)
            {
             LEDDurumuYesil=1;
            }
            else
            {
             LEDDurumuYesil=0;
            }
          }break;
      }  
    }
    break;
    
    case 2:
      KirmiziYesil();
      switch(ButonDurumu)
      {
         case KIRMIZI:
         {
          if(digitalRead(LED_Kirmizi)==LOW)
          {
           digitalWrite(LED_Kirmizi,HIGH);
          }
          else
          {
            digitalWrite(LED_Yesil,LOW);
            digitalWrite(LED_Kirmizi,LOW);
          }
          
          ButonDurumu=0;
          
         }
         break;
         
         case YESIL:
         {
          if(digitalRead(LED_Yesil)==HIGH)
          {
           digitalWrite(LED_Yesil,LOW);
          }
          else
          {
            digitalWrite(LED_Yesil,HIGH);
            digitalWrite(LED_Kirmizi,HIGH);
          }
          ButonDurumu=0;
         }
         break;
      }
      break;
      
    case 3:
    //ButonAcma();
    break;
    
    case 4:
    //ButonAcma();    
    break;
    
    case 5:
    //ButonAcma();
    break;
    
    case 6:
    //ButonAcma();    
    break;
    
    case 7:    
   // ButonAcma();
    break;
  }

}
void KirmiziButon()
{
  if(digitalRead(ButonK))
  {
   while(digitalRead(ButonK));
   ButonDurumu=KIRMIZI;  
  }
} 
void YesilButon()
{
  if(digitalRead(ButonY))
  {
   while(digitalRead(ButonY));
   ButonDurumu=YESIL;  
  }
  if(LEDDurumuYesil==1)
  {
     if(digitalRead(ButonK))
     {
      while(digitalRead(ButonK));
      ButonDurumu=KIRMIZI;
     }
  }
}
void KirmiziYesil()
{
  if(digitalRead(ButonK))
  {
   while(digitalRead(ButonK));
   ButonDurumu=KIRMIZI;

  }
  if(digitalRead(ButonY))
  {
   while(digitalRead(ButonY));
   ButonDurumu=YESIL;
  
  }
}   
   

 
