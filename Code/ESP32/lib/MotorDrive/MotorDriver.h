#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <Arduino.h>

class MotorDriver{
    int ain1, ain2, pwma, bin1, bin2, pwmb, stby;
    int A, B;
    public:
        MotorDriver(int, int, int, int, int, int);
        void MotorRL(int, int);
};

#endif