#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;
int pozycjaPrzeszkody = 0;
int pozycjaGracza = 4;
unsigned long czas = 0;
int wysokoscGracza = 6;
int wysokoscPrzeszkody[4]={199,227,143,241};
int przeszkoda=0;
bool over = false;
bool in = false;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;
byte gameOver[8];
byte gra[8];
LedControl lc = LedControl(DIN,CLK,CS,0);

void setup() 
{
  pinMode(9, INPUT_PULLUP);
  lc.shutdown(0,false);
  lc.setIntensity(0,10);
  lc.clearDisplay(0);
  Serial.begin(9600);
}

void loop() 
{
  czas = millis();
  
  //if(digitalRead(9)==HIGH)
  //{
  //  Serial.println("out");
  //}
  //else
  //{
  //  Serial.println("in");
  //}  

  Serial.print("Wysokosc gracza: ");
  Serial.println(wysokoscGracza);

  Serial.print("Pozycja gracza: ");
  Serial.println(pozycjaGracza);    
  
  pozycjaGracza = lround(pow(2,wysokoscGracza));

  if(!over)
  {
    //byte gra[8] = {0,0,0,0,0,0,pozycjaGracza,0};
    if(pozycjaPrzeszkody==0)
    {
      //if(
      gra[0]=wysokoscPrzeszkody[przeszkoda];
    }
    else
    {
      gra[0]=1;
    }
    if(pozycjaPrzeszkody==1)
    {
      gra[1]=wysokoscPrzeszkody[przeszkoda];
    }
    else
    {
      gra[1]=1;
    }
    if(pozycjaPrzeszkody==2)
    {
      gra[2]=wysokoscPrzeszkody[przeszkoda];
    }
    else
    {
      gra[2]=1;
    }
    if(pozycjaPrzeszkody==3)
    {
      gra[3]=wysokoscPrzeszkody[przeszkoda];
    }
    else
    {
      gra[3]=1;
    }
    if(pozycjaPrzeszkody==4)
    {
      gra[4]=wysokoscPrzeszkody[przeszkoda];
    }
    else
    {
      gra[4]=1;
    }
    if(pozycjaPrzeszkody==5)
    {
      gra[5]=wysokoscPrzeszkody[przeszkoda];
    }
    else
    {
      gra[5]=1;
    }
    if(pozycjaPrzeszkody==6)
    {
      gra[6]=wysokoscPrzeszkody[przeszkoda]+pozycjaGracza;
    }
    else
    {
      gra[6]=pozycjaGracza+1;
    }
    if(pozycjaPrzeszkody==7)
    {
      gra[7]=wysokoscPrzeszkody[przeszkoda];
    }
    else
    {
      gra[7]=1;
    }
    printByte(gra);

    if(wysokoscGracza == 0)
    {
      over = true;
    }

    roznicaCzasu = czas - zapamietanyCzas;
    if (roznicaCzasu >= 500UL)
    {
      zapamietanyCzas = czas;
      if(wysokoscGracza>0)
      {
        wysokoscGracza-=1;
        pozycjaPrzeszkody+=1;
        if(pozycjaPrzeszkody>7)
        {
          przeszkoda=random(4);
          pozycjaPrzeszkody=0;        
        }
      }
    }
    if(digitalRead(9)==LOW && in==false)
    {
      wysokoscGracza+=1;      
      in=true;
    }
    
    if(digitalRead(9)==HIGH)
    {
      in=false;
    }
  }
  else
  {
    //byte gameOver[8] = {129,66,36,24,24,36,66,129};
    gameOver[0]=129;
    gameOver[1]=66;
    gameOver[2]=36;
    gameOver[3]=24;
    gameOver[4]=24;
    gameOver[5]=36;
    gameOver[6]=66;
    gameOver[7]=129;
    printByte(gameOver);

    if(digitalRead(9)==LOW)
    {
      pozycjaGracza=4;
      wysokoscGracza=6;
      over=false;
    }
  }  
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
