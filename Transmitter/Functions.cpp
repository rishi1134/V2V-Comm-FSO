#include "Functions.h"
#include <stdbool.h>
#include <Arduino.h>

static int frame;
static int bCount=0;
static int memBit;
int sensorValue = 0;
int sensorPin = 2;
unsigned long TIMEOUT = 1500;
unsigned long timeOutStart;
    
int Functions:: concatData(int a,int i,int field)  //1011000000000
{
  if(i!=-1)
    switch(field)
    {
      case 4:
        i= (i & 8190) | a;
        break;
      case 3:
        i= (i & 8189) | a;
        break;
      case 2:
        i= (i & 7683) | a;
        break;
      case 1:
        i= (i & 511) | a;
        break;
    }
  else
    i= 5632 | a;
  return i;
}

int Functions:: DataFramer(bool statusFlag,int key,int field)
{
  //long int key=getKey();         //for Lane it will be - 0000000000000000-10-1
  if(!statusFlag)
    frame=concatData(key,-1,field);
  else
    frame=concatData(key,frame,field);
  return frame;
}

bool Functions:: bitTransmit(int data)
{
  int i=12;
  int j=3;
  while (i >= 0) {
    if ((data >> i) & 1)
    {
      if(i<9)
        bitStuff(1);
      digitalWrite(16,HIGH);
      Serial.print("1");
      delay(1000);
    }
    else
    {
      if(i<9)
        bitStuff(0);
      digitalWrite(16,LOW);
      Serial.print("0");
      delay(1000);
    }
    i--;
  }
  //Serial.println();
  int data1=10;
  while (j >= 0) {
    if ((data1 >> j) & 1)
    {
      digitalWrite(16,HIGH);
      Serial.print("1");
      delay(1000);
    }
    else
    {
      digitalWrite(16,LOW);
      Serial.print("0");
      delay(1000);
    }
    j--;
  }
  Serial.println();
  //delay(1000);
  return ackCheck();
}

bool Functions::ackCheck()
{
  timeOutStart=millis();
  while(millis()-timeOutStart <= TIMEOUT)         //Timeout timer =1.5sec
  {
    sensorValue=analogRead(A0);
    if(sensorValue>=1000 && sensorValue<=1024)
    {
      return true;
    }
  }
  Serial.println("Connection TIMED-OUT");
  return false;
}

void Functions::bitStuff(int i)
{
  if(i==1 && bCount==0)
  {
    bCount++;
    return;
  }
  else if(i==0 && bCount==1)
  {
    bCount++;
    return;
  }
  else if(i==1 && bCount==2)
  {
    bCount++;
    return;
  }
  else if(i==1 && bCount==3)
  {
    bCount=0;
    digitalWrite(16,LOW);
    Serial.print("0");
    delay(1000);
    return;
  }
  else
  {
     bCount=0;
     if(i==1 && bCount==0)
      {
        bCount++;
        return;
      }
  }
  return;
}
