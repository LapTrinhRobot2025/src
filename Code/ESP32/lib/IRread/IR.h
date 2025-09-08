#ifndef IR_H
#define IR_H

#include <Arduino.h>

class IR
{
private:
    int S0, S1, S2, S3, SIG;
public:
    IR(int, int, int, int, int);
    void selectChannel(uint8_t);
    void readIR(int[]);
    void inIR(int []);
};

#endif
