#ifndef MAKINA_H_
#define MAKINA_H_

#define KIRMIZI_LED    13
#define YESIL_LED      0
#define ALARM_LED      1 

#define KIRMIZI_BUTTON 8
#define YESIL_BUTTON   9      

#define KIRMIZI_ON()        digitalWrite(KIRMIZI_LED,HIGH)
#define YESIL_ON()          digitalWrite(YESIL_LED,LOW)
#define ALARM_ON()          digitalWrite(ALARM_LED,LOW)

#define KIRMIZI_OFF()       digitalWrite(KIRMIZI_LED,LOW)
#define YESIL_OFF()         digitalWrite(YESIL_LED,HIGH)
#define ALARM_OFF()         digitalWrite(ALARM_LED,HIGH)

#define READ(PIN)           digitalRead(PIN)
uint8_t ButtonState=0;
uint8_t ButtonNewState=0;
const uint8_t Kirmizi=1;
const uint8_t Yesil=2;
int a=0;
void BUTTON_READING();
void BUTTON_STATE();



void BUTTON_READING()
{
	if(READ(KIRMIZI_BUTTON))
	{
		while(READ(KIRMIZI_BUTTON));
		ButtonState=Kirmizi;
		ButtonNewState=ButtonState;
		ButtonState=0;
	}
	if(READ(YESIL_BUTTON))
	{
		while(READ(YESIL_BUTTON));
		ButtonState=Yesil;
		ButtonNewState=ButtonState;
		ButtonState=0;
	}
}
void BUTTON_STATE()
{
	if(ButtonNewState==Kirmizi)
	{
		if(READ(YESIL_BUTTON))
		{
			while(READ(YESIL_BUTTON));
			ButtonState=Yesil;
      
		}
	}
	if(ButtonNewState==Yesil)
	{
		if(READ(YESIL_BUTTON))
		{
			while(READ(YESIL_BUTTON));
			ButtonState=Yesil;
      a=0;
		}
		if(READ(KIRMIZI_BUTTON))
		{
			while(READ(KIRMIZI_BUTTON));
			ButtonState=Kirmizi;
      a=0;
		}
	}
	
}

 #endif 
