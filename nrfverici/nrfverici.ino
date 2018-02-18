////////MEGA VERİCİ/////////////////////////////////////////////////////////
#include <Rotary.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Timer.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SW 4
#define OLED_RESET 4
#define psw 10
#define osw 9
///////////////////////////////////////////////////////////////////////////
Timer t;
Adafruit_SSD1306 display(OLED_RESET);
RF24 radio(5, 6); //radio(CE, CS);
const uint64_t kod = 0xE8E8F0F0E1LL;
Rotary r = Rotary(2, 3);
int adt=0;
int sayi[7]={0};
int flagsw;
int buton;
int menu=1;
int pot;
int flag;
////////////////////////////////////////////////////////////////////////////////////////////
void drawmen()//panel ayar 
{
    unsigned char result = r.process();//rotary encoder degerini alma    
    if (result == DIR_CW) 
      {
      
          //kont=1;
          menu+=1;
          if (menu<1)// 0 olmaması için
            {
              menu=6;
            }
          if (menu>6)//3 den 1 e dön
            {
              menu=1;
            }
          menuayar();
          selayar();
      
      }
    else if (result == DIR_CCW)
      {         
        menu-=1;
        if (menu<1)
          {
            menu=6;
          }
        if (menu>6)
          {
            menu=1;
          }        
        menuayar();
        selayar();
      }
    else if (result == DIR_NONE)
      {
               
      }
}

////////////////////////////////////////////////////////////////////////////
 void rot()//zaman ayarlama
{
    pot=sayi[menu];//girilen panelin en son degerini al     
    unsigned char result = r.process();    
    if (result == DIR_CW) 
      {      
        pot+=5;
        if(pot<0)
          {pot=0;}      
        sayi[menu] = pot;//ayarlanan degeri ilgili panele ayarla
        zmnayar();
        ayarsel();
        Serial.println(pot);
      }
    else if (result == DIR_CCW)
      {
        //kont=1; 
        pot-=5; 
        if(pot<0)
        {pot=0;}        
        sayi[menu] = pot;
        zmnayar();
        ayarsel();
        /*display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(32,0);
        display.println("ayar");
        display.display();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(32,16);
        display.println(pot);
        display.display();*/
        Serial.println(pot);
      }
    else if (result == DIR_NONE)
      {
         sayi[menu] = pot;
         Serial.println(pot);
      }
    buton=digitalRead(SW);
    if (buton==0)
      {
        flagsw=0;
      }
        
} 
    
///////////////////////////////////////////////////////////////////////////
void butonkontrol()//zaman ayar ekranına girme ve cıkma
{
     
    buton=digitalRead(SW);//butonu oku
    while(buton==0)
      {         
        Serial.println("buton 0");
        buton=digitalRead(SW);        
        if (buton==1)
          {            
            Serial.println("buton 1");
            if (flagsw==0)
              {
                flagsw=1;
                Serial.println("flag 1");break;
              }
            else
              {            
                flagsw=0;
                Serial.println("flag 0");break;
              }
          }       
      }
}
  ////////////////////////////////////////////////////////////////////////////
  void zmnayar()//zaman ayarlama ekranı 
  {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(50,0);
        display.println("Ayar");
        display.display();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(50,16);
        display.println(sayi[menu]);
        display.display();    
  }
  ////////////////////////////////////////////////////////////////////////////////////////
  void menuayar()//panel ayarlama ekranı
  {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(50,0);
        display.println("MENU");
        display.display();    
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(50,16);
        display.println(menu);
        display.display();    
  }
  /////////////////////////////////////////////////////////////////////////////////////
  void ayarsel()//zaman ayar ekranında panel no yazma
  {        
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println(menu);
        display.display();    
  }  
  //////////////////////////////////////////////////////////////////////////////
    void selayar()// panel ayarlama ekranında eski zaman ayarını yazma
  {        
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println(sayi[menu]);
        display.display();    
  }
  ///////////////////////////////////////////////////////////////////////////
void sending()//veri gönderme
{
    //adt++;Serial.print("adt="); Serial.println(adt);//göndrme sayısı
    int ssw=digitalRead(psw);//butonu oku
    int ssw2=digitalRead(osw);//butonu oku
    if (ssw==0&ssw2==0)sayi[0]=0;
    if (ssw==1)sayi[0]=1;
    if (ssw2==1)sayi[0]=2; 
    radio.write(sayi, sizeof(sayi));//gönder
    Serial.println(sayi[0]);
    Serial.println("sending");
    switch(menu)
      {      
        case 1:
                radio.write(sayi, sizeof(sayi));
                Serial.println("sending");
                Serial.println(sayi[1]);break;
       case 2:
                radio.write(sayi, sizeof(sayi));
                Serial.println("sending");
                Serial.println(sayi[2]);break;
        case 3:
                radio.write(sayi, sizeof(sayi));
                Serial.println("sending");
                Serial.println(sayi[3]);break;    
      }
} 
///////////////////////////////////////////////////////////////////////////
void sendbuton()
{
  sayi[0]=2;
  sending();
}
///////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,0);
  display.println("elektrobil");
  t.every(500, sending);// 2 sn de bi gönder 
  display.display();
  delay(1000);
  pinMode(psw, INPUT);
  pinMode(osw, INPUT);
  //attachInterrupt(digitalPinToInterrupt(osw), sendbuton, HIGH);
  display.clearDisplay();
  radio.begin();
  radio.openWritingPipe(kod);
}
///////////////////////////////////////////////////////////////////////////
void loop()
{
  t.update();  
  menuayar();
  selayar();
  while(flagsw==0)// menude kal
      {
        t.update();              
        drawmen();
        butonkontrol();   
      }    
  zmnayar(); 
  ayarsel();
  while (flagsw==1)//zaman ayarlama yapmaya basla
     {        
        rot();              
     }
     
  for(int i=0;i<4;i++)
     {
       Serial.print("sayi[i]:");Serial.println(sayi[i]);
     }
}


