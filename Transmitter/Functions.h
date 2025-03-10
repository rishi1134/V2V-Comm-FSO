#ifndef _Functions_H
#define _Functions_H
#include <stdbool.h>
#include <Arduino.h>

class Functions {
  public:
    int concatData(int a,int i,int field);
    int DataFramer(bool statusFlag,int key,int field);
    bool bitTransmit(int data);
    bool ackCheck();
    void bitStuff(int i);
};
#endif
