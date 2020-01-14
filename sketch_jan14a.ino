#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;
int pozycjaPrzeszkody = 0;
int przyspieszenie = 500;
int pozycjaGracza = 4;
unsigned long czas = 0;
int wysokoscGracza = 6;
int wysokoscPrzeszkody[4]={199,227,143,241};
int przeszkoda=0;
bool over = false;
bool in = false;
int wynik = 0;
int koniecEtap = 0;
unsigned long zapamietanyCzas = 0;
unsigned long zapamietanyCzas2 = 0;
unsigned long zapamietanyCzas3 = 0;
unsigned long zapamietanyCzas4 = 0;
unsigned long roznicaCzasu = 0;
unsigned long roznicaCzasu2 = 0;
unsigned long roznicaCzasu3 = 0;
unsigned long roznicaCzasu4 = 0;

byte gameOver[8];
byte gra[8];

byte zero[8] = {0, 0, 60, 66, 66, 60, 0, 0};
byte jeden[8] = {0, 0, 0, 126, 32, 0, 0, 0};
byte dwa[8]={0, 0, 114, 82, 82, 94, 0, 0};
byte trzy[8] = {0, 0, 126, 82, 82, 82, 0, 0};
byte cztery[8] = {0, 0, 126, 16, 16, 112, 0, 0};
byte piec[8] = {0, 0, 94, 82, 82, 114, 0, 0};
byte szesc[8] = {0, 0, 94, 82, 82, 126, 0, 0};
byte siedem[8] = {0, 0, 96, 94, 64, 64, 0, 0};
byte osiem[8] = {0, 0, 126, 82, 82, 126, 0, 0};
byte dziewiec[8] = {0, 0, 126, 82, 82, 114, 0, 0};
byte wiecej[8] = {16, 56, 16, 0, 126, 82, 82, 114};

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

  //Serial.print("Wysokosc gracza: ");
  //Serial.println(wysokoscGracza);

  //Serial.print("Pozycja gracza: ");
  //Serial.println(pozycjaGracza);

  //Serial.print("Przeszkoda: ");
  //Serial.println(przeszkoda);

  Serial.print("Wyswietlacz: ");
  Serial.println(gra[6]);
  
  pozycjaGracza = lround(pow(2,wysokoscGracza));

  if(!over)
  {    
    if(pozycjaPrzeszkody==0)
    {
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
      switch(przeszkoda)
      {
        case 0:
          if(gra[6]!=231 && gra[6]!=215 && gra[6]!=207)
          {
            over=true;
          }
        break;
        case 1:
          if(gra[6]!=243 && gra[6]!=235 && gra[6]!=231)
          {
            over=true;
          }
        break;
        case 2:
          if(gra[6]!=159 && gra[6]!=207 && gra[6]!=175)
          {
            over=true;
          }
        break;
        case 3:
          if(gra[6]!=249 && gra[6]!=245 && gra[6]!=243)
          {
            over=true;
          }
        break;
      }
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
    roznicaCzasu2 = czas - zapamietanyCzas2;
    roznicaCzasu3 = czas - zapamietanyCzas3;

    if(roznicaCzasu2 >= 6000 && przyspieszenie>100)
    {
      zapamietanyCzas2 = czas;
      przyspieszenie-=100;
    }
    
    if (roznicaCzasu >= przyspieszenie)
    {
      zapamietanyCzas = czas;
      if(wysokoscGracza>0)
      {        
        pozycjaPrzeszkody+=1;
        if(pozycjaPrzeszkody>7)
        {
          przeszkoda=random(4);
          wynik+=1;
          pozycjaPrzeszkody=0;        
        }
      }      
    }

    if(roznicaCzasu3 >= 500)
    {
      zapamietanyCzas3=czas;
      if(wysokoscGracza>0)
      {
        wysokoscGracza-=1;
      }
    }
    
    if(digitalRead(9)==LOW && in==false && wysokoscGracza<7)
    {
      wysokoscGracza+=1;      
      in=true;
    }
    
    if(digitalRead(9)==HIGH)
    {
      in=false;
    }

    roznicaCzasu4=0;
    zapamietanyCzas4=0;
    koniecEtap=0;
  }
  else
  {
    if(koniecEtap!=1)
    {
      roznicaCzasu4 = czas - zapamietanyCzas4;

      if(roznicaCzasu4 >= 5000)
      {
        zapamietanyCzas4 = czas;      
        koniecEtap+=1;
      }
    }
    
    if(koniecEtap==0)
    {      
      gameOver[0]=129;
      gameOver[1]=66;
      gameOver[2]=36;
      gameOver[3]=24;
      gameOver[4]=24;
      gameOver[5]=36;
      gameOver[6]=66;
      gameOver[7]=129;
      printByte(gameOver);      
    }
    if(koniecEtap==1)
    {
      switch(wynik)
      {
        case 0:
          printByte(zero);
        break;
        case 1:
          printByte(jeden);
        break;
        case 2:
          printByte(dwa);
        break;
        case 3:
          printByte(trzy);
        break;
        case 4:
          printByte(cztery);
        break;
        case 5:
          printByte(piec);
        break;
        case 6:
          printByte(szesc);
        break;
        case 7:
          printByte(siedem);
        break;
        case 8:
          printByte(osiem);
        break;
        case 9:
          printByte(dziewiec);
        break;
        default:
          printByte(wiecej);
        break;
      }

      if(digitalRead(9)==LOW)
      {
        pozycjaGracza=4;
        wysokoscGracza=6;
        przyspieszenie=500;
        pozycjaPrzeszkody=0;        
        wynik=0;
        przeszkoda=random(4);
        czas=0;
        over=false;
      }
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
