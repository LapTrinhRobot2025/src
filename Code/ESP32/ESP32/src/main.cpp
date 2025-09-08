#include <Arduino.h>

// Chân chọn kênh
int S0 = 27;
int S1 = 26;
int S2 = 25;
int S3 = 33;

#define NUM_SENSORS 16   // dùng đủ 16 kênh IR

int irValues[NUM_SENSORS];  // Mảng lưu giá trị cảm biến

// Hàm chọn kênh multiplexer (0..15)
void selectChannel(uint8_t channel) {
  digitalWrite(S0, channel & 0x01);
  digitalWrite(S1, (channel >> 1) & 0x01);
  digitalWrite(S2, (channel >> 2) & 0x01);
  digitalWrite(S3, (channel >> 3) & 0x01);
}

void setup() {
  Serial.begin(115200);

  // Cấu hình các chân điều khiển multiplexer là output
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
}

void loop() {
  // Quét toàn bộ 16 kênh 
  for (int i = 0; i < NUM_SENSORS; i++) {
    selectChannel(i);                 // chọn kênh i
    delayMicroseconds(5);             // chờ tín hiệu ổn định
    irValues[i] = analogRead(34); // đọc ADC từ cảm biến
  }

  // In ra giá trị để quan sát
  Serial.print("IR values: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(irValues[i]);
    Serial.print("\t");
  }
  Serial.println();

  delay(1000); // delay nhỏ để dữ liệu mượt
}