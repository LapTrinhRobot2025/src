// ...existing code...
#include <Wire.h>
#include "MPU6050.h"
#include "dcMotor.h"
MPU6050 mpu;


// Tham số PD
float Kp = 15.0;   // Hệ số tỉ lệ
float Kd = 0.8;    // Hệ số vi phân

float targetAngle = 0; // Góc cân bằng mong muốn (thẳng đứng)
float lastError = 0;

void setup() {
    Wire.begin();
    mpu.initialize();
    // motor đã được khởi tạo ở trên
}

void loop() {
    // Đọc giá trị pitch từ MPU6050
    float pitch = getPitch(); // Bạn cần cài đặt hàm này để trả về góc nghiêng

    // Tính toán PD
    float error = pitch - targetAngle;
    float derivative = error - lastError;
    float output = Kp * error + Kd * derivative;

    // Giới hạn tốc độ động cơ
    int speed = constrain(abs(output), 0, 255);

    if (output > 0) {
        // Nghiêng về phía trước, lùi lại
     
    } else if (output < 0) {
        // Nghiêng về phía sau, tiến lên
        
    } else {
       // dừng 
    }

    lastError = error;
    delay(10); // Chu kỳ điều khiển
}

// Hàm đọc pitch từ MPU6050 (ví dụ, bạn cần tự cài đặt)
float getPitch() {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
    return pitch;
}