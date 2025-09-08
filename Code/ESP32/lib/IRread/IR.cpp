#include "IR.h"

#include <Arduino.h>

IR::IR(int a, int b, int c, int d, int e){
    S0 = a;
    S1 = b;
    S2 = c;
    S3 = d;
    SIG = e;
    
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
}

void IR::selectChannel(uint8_t channel)
{
  digitalWrite(S0, channel & 0x01);
  digitalWrite(S1, (channel >> 1) & 0x01);
  digitalWrite(S2, (channel >> 2) & 0x01);
  digitalWrite(S3, (channel >> 3) & 0x01);
}

void IR::readIR(int IRval[]){
    for (int i = 0; i < 16; i++)
    {
        selectChannel(i);             // chọn kênh i
        delayMicroseconds(5);         // chờ tín hiệu ổn định
        IRval[i] = analogRead(SIG); // đọc ADC từ cảm biến
    }
}

void IR::inIR(int IRval[]){
    readIR(IRval);
    Serial.print("IR Values: ");
    for (int i = 0; i < 16 ; i++){
        Serial.print(IRval[i]);
        Serial.print("\t");
    }
    Serial.println();
    delay(1000);
}

