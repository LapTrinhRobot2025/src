#include "MotorDriver.h"
#include <Arduino.h>

MotorDriver::MotorDriver(int a, int b, int c, int d, int e, int f){
    ain1 = a;
    ain2 = b;
    pwma = c;
    bin1 = d;
    bin2 = e;
    pwmb = f;
    ledcSetup(A, 1000, 8);    // PWM: 1kHz, 8 bit (0-255)
    ledcAttachPin(pwma, A);
    ledcSetup(B, 1000, 8);    // PWM: 1kHz, 8 bit (0-255)
    ledcAttachPin(pwmb, B);
}

void MotorDriver::MotorRL(int Pwma, int Pwmb){
    if (Pwma > 0){
        digitalWrite(ain1, HIGH);
        digitalWrite(ain2, LOW);
    }
    else{
        digitalWrite(ain2, HIGH);
        digitalWrite(ain1, LOW);
        Pwma = -Pwma;
    }
    if (Pwmb > 0){
        digitalWrite(bin1, HIGH);
        digitalWrite(bin2, LOW);
    }    
    else {
        digitalWrite(bin2, HIGH);
        digitalWrite(bin1, LOW);
        Pwmb = -Pwmb;        
    }
    ledcWrite(A, Pwma);
    ledcWrite(B, Pwmb);
}

