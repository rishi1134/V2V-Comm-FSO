#include "Functions.h"
//#include <LiquidCrystal.h>

//const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;   
//LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

const int p=D7;
int sensorPin = A0; // select the input pin for ldr

void setup()
{
    Serial.begin(115200);
    //pinMode(5, OUTPUT); //pin connected to the LED
    //lcd.begin(20, 4);
    //lcd.setCursor(0, 0);
    //lcd.print("V2V Hello");
    //pinMode(p,INPUT);
}

Functions f=*new Functions();
void loop()
{
    //Serial.println(digitalRead(p));
    //if(!digitalRead(p)){
    //double thresh=f.Calibrate();
    String frame=f.dataRecv(A0);
    //Serial.println(frame);
    if(f.headerCheck(frame))
    {
      int Lane=f.getLane(frame);
      int Brake=f.getBrake(frame);
      int Speed=f.getSpeed(frame);
      Serial.println(Lane);
      Serial.println(Brake);
      Serial.println(Speed);
      //f.ackTrans();
      /*lcd.print(Lane);
      lcd.setCursor(0, 1);
      lcd.print(Brake);
      lcd.setCursor(0, 0);
      lcd.print(Speed);*/
    }
    //lcd.clear();
    //}
}
