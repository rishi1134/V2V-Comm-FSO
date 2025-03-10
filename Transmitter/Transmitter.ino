//total 28sec delay
#include "Functions.h"
#include <Keypad.h>
#include <Arduino.h>
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};

byte rowPins[ROWS] = { D7, D6, D5, D4};
byte colPins[COLS] = { D3, D2, D1, D8};
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int dataFrame;
int fullFrame;
bool statusFlag=false;
static int initSpeed=10;

void setup()
{
  Serial.begin(115200);
  
  pinMode(16,OUTPUT);
  
}
Functions f=*new Functions();
void loop()
{
  char key = kpd.getKey();
  if (key != NO_KEY)
  {
      Serial.println(key);
      switch(key)
      {
        case '4':
          //Lane change - Left - 0
          dataFrame=0;
          fullFrame=f.DataFramer(statusFlag,dataFrame,4);
          while(!f.bitTransmit(fullFrame))
          {delay(2);}
          statusFlag=true;
          break;
        case '6':
          //Lane change - Right - 1
          dataFrame=1;
          fullFrame=f.DataFramer(statusFlag,dataFrame,4);
          while(!f.bitTransmit(fullFrame))
          {delay(2);}
          statusFlag=true;
          break;
        case '8':
          //Braking - 1
          dataFrame=2;
          fullFrame=f.DataFramer(statusFlag,dataFrame,3);
          while(!f.bitTransmit(fullFrame))
          {delay(2);}
          statusFlag=true;
          break;
        case '2':
          //Speed Inc by 1
          initSpeed=(initSpeed+1)*4;
          dataFrame=initSpeed;
          fullFrame=f.DataFramer(statusFlag,dataFrame,2);
          while(!f.bitTransmit(fullFrame))
          {delay(2);}
          statusFlag=true;
          break;
        default:
          //Invalid Input
          dataFrame=3000;
          fullFrame=f.DataFramer(statusFlag,dataFrame,1);
          while(f.bitTransmit(fullFrame))
          {delay(2);}
          break;
      }
  }
}   
