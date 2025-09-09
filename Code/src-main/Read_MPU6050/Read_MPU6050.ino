#include <Wire.h>

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
int16_t AcX = 0, AcY = 0, AcZ = 0, Tmp = 0, GyX = 0, GyY = 0, GyZ = 0;

void setup() {
Serial.begin(115200);
Wire.begin(21, 22, 100000); // SDA, SCL, Clock Speed
Wire.beginTransmission(MPU_ADDR);
Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // Wake up MPU-6050
Wire.endTransmission(true);
Serial.println("Setup complete");
}
int GX[10] = {0};
int GY[10] = {0};
int GZ[10] = {0};
void loop() {
Wire.beginTransmission(MPU_ADDR);
Wire.write(0x3B); // Starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(true);

Wire.requestFrom(MPU_ADDR, 14, true); // Request a total of 14 registers
// AcX = Wire.read() << 8 | Wire.read(); // ACCEL_XOUT_H & ACCEL_XOUT_L
// AcY = Wire.read() << 8 | Wire.read(); // ACCEL_YOUT_H & ACCEL_YOUT_L
// AcZ = Wire.read() << 8 | Wire.read(); // ACCEL_ZOUT_H & ACCEL_ZOUT_L
// Tmp = Wire.read() << 8 | Wire.read(); // TEMP_OUT_H & TEMP_OUT_L
for(int i = 0; i < 10; i++)
{
  GyX = Wire.read() << 8 | Wire.read(); // GYRO_XOUT_H & GYRO_XOUT_L
  GX[i] += GyX;
  GyY = Wire.read() << 8 | Wire.read(); // GYRO_YOUT_H & GYRO_YOUT_L
  GY[i] += GyY;
  GyZ = Wire.read() << 8 | Wire.read(); // GYRO_ZOUT_H & GYRO_ZOUT_L
  GZ[i] += GyZ;
}


// Serial.print("AcX: "); Serial.print(AcX);
// Serial.print(" AcY: "); Serial.print(AcY);
// Serial.print(" AcZ: "); Serial.print(AcZ);
Serial.print(" GyX: "); Serial.print(giatritb(GX));
Serial.print(" GyY: "); Serial.print(giatritb(GY));
Serial.print(" GyZ: "); Serial.print(giatritb(GZ));
Serial.println();
delay(1000);
}
int giatritb(int value[])
{
  int sum = 0;
  for(int i = 0; i < 10; i++)
  {
    sum += value[i];
  }
  return sum / 10;
}