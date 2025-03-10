#include "Functions.h"
#include <stdbool.h>
#include <Arduino.h>
#include <math.h>

String H="1";
String L="0";
static int bCount;
static String d="";
static int ht=0;

double Functions:: Calibrate()
{
  int sensorVal=0;
  for(int i=0;i<10;i++)
  {
    sensorVal+=analogRead(A0);
  }
  return sensorVal/10;
}

bool Functions:: headerCheck(String data)
{
  if(data.substring(0,4)=="1011")
  {
    return true;
  }
  return false;
}

String Functions:: dataRecv(int sensorPin)
{
  d="";
  int sensorVal;
  int tempVal=0;
  int i=0;
  int bi=0;
  ht=0;
  do
  {
  sensorVal=analogRead(A0); 
  if(sensorVal>=410)
  {bi=1;
  Serial.print("1");}
  else
  {bi=0;
  Serial.print("0");}
  delay(1000);
  }while(headerCheck(bi)!=1);
  ht=1;
  Serial.println("Header Done");
  if(ht)  {
  do
  {
    sensorVal=analogRead(A0); 
    if(sensorVal>=410)
    {bi=1;
    d+="1";
    Serial.print("1");}
    else
    {bi=0;
    d+="0";
    Serial.print("0");}
    delay(1000);
    }while(trailerCheck(bi)!=1);
  }
  Serial.println("done");
  Serial.println(d);
  return d;
}

int Functions::getLane(String data)
{
  int a=data.substring(12,13).toInt();
  return a;
}

int Functions:: getBrake(String data)
{
  int a=data.substring(11,12).toInt();
  return a;
}

int Functions:: getSpeed(String data)
{
  int a[7];
  String d=data.substring(4,11);
  for(int i=0;i<7;i++)
  {
    a[i]=d.substring(i,i+1).toInt();
  }
  return bin2dec(a); 
}

int Functions:: bin2dec(int sensorValList[])
{
  int i=6;
  int add=0,temp=1,k;
  for(int h=0;h<7;h++)
  {
    add=add+sensorValList[h]*((int)pow(2,(double)i));
    i--;
  }
  return add;
}

void Functions:: ackTrans()
{
  digitalWrite(5,HIGH);
  delay(500);
  digitalWrite(5,LOW);
}

int Functions::headerCheck(int i)
{
  if(i==1 && bCount==0)
  {
    bCount++;
    return 0;
  }
  else if(i==0 && bCount==1)
  {
    bCount++;
    return 0;
  }
  else if(i==1 && bCount==2)
  {
    bCount++;
    return 0;
  }
  else if(i==1 && bCount==3)
  {
    bCount=0;
    d="1011";
    return 1;
  }
  else
  {
     bCount=0;
     if(i==1 && bCount==0)
      {
        bCount++;
        return 0;
      }
  }
  return -1;
}

int Functions::trailerCheck(int i)
{
  if(i==1 && bCount==0)
  {
    //d+="1";
    bCount++;
    return 0;
  }
  else if(i==0 && bCount==1)
  {
    //d+="0";
    bCount++;
    return 0;
  }
  else if(i==1 && bCount==2)
  {
    //d+="1";
    bCount++;
    return 0;
  }
  else if(i==0 && bCount==3)
  {
    //d+="b1010";
    bCount=0;
    return 1;
  }
  else
  {
     bCount=0;
     if(i==1 && bCount==0)
      {
        //d+="1";
        bCount++;
        return 0;
      }
  }
  return -1;
}
