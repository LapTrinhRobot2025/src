#include <Arduino.h>
#include "IR.h"
#include "MotorDriver.h"

// Chân chọn kênh

int IRval[16];

IR IRline(23,22,21,19,15);
MotorDriver motor(14, 12, 13, 25, 33, 32);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  // motor.MotorRL(255, 255);
  IRline.inIR(IRval);
}