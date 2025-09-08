#include <Arduino.h>

// Chân điều khiển TB6612FNG
#define AIN1 25
#define AIN2 26
#define PWMA 27   // PWM để điều chỉnh tốc độ motor

void setup() {
  // Cấu hình chân output
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  // Ban đầu motor dừng
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0); // tốc độ 0%
}

void loop() {
  // Nếu Ain1=1 và Ain2=1 => motor chạy
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);

  // bật PWM 100% (tốc độ tối đa)
  analogWrite(PWMA, 255);

  delay(2000); // chạy 2s

  // Motor dừng
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0);

  delay(2000); // nghỉ 2s
}
