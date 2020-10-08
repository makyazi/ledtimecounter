#include "makina.h"


void setup() 
{
  pinMode(KIRMIZI_LED,OUTPUT);
  pinMode(YESIL_LED,OUTPUT);
  pinMode(ALARM_LED,OUTPUT);

  pinMode(KIRMIZI_BUTTON,INPUT);
  pinMode(YESIL_BUTTON,INPUT); 

  KIRMIZI_OFF();
  YESIL_OFF();
  ALARM_OFF();
}

void loop() 
{
  BUTTON_READING();

  switch(ButtonNewState)
  {
   case Kirmizi:
   {
    KIRMIZI_ON();
    for(int sure=0;sure<5000;sure++)
    {
      delay(1);
      BUTTON_STATE();
      if(ButtonState==Yesil)
      {
       ALARM_ON();
      }
    }
     KIRMIZI_OFF();
     ALARM_OFF();
     ButtonNewState=0;
   }
   break;

   case Yesil:
   {
    YESIL_ON();
    a=1;
    while(a==1)
    {
      BUTTON_STATE();
    }
    if(ButtonState==Yesil)
    {
     YESIL_OFF();
     ButtonNewState=0;
     ButtonState=0;
    }
    if(ButtonState==Kirmizi)
    {
     YESIL_OFF();
     ButtonState=0;
     ButtonNewState=Kirmizi;
    } 
   }
   break;
  }

}
