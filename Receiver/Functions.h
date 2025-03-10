//Header Functions.h
#ifndef _Functions_H
#define _Functions_H
#include <stdbool.h>
#include <Arduino.h>

class Functions {
  public:
    int bin2dec(int sensorValList[]);
    bool headerCheck(String data);
    int headerCheck(int i);
    String dataRecv(int sensorPin);
    int getLane(String data);
    int getBrake(String data);
    int getSpeed(String data);
    void ackTrans();
    double Calibrate();
    int trailerCheck(int i);
};
#endif
