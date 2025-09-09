#include "motor.h"


const int freq = 5000;
const int resolution = 8;  // PWM 8-bit (0-255)
int _pwmL, _in1L, _in2L;
int _pwmR, _in1R, _in2R;
int _pwmChannelL, _pwmChannelR;
motor :: motor(int pwmL, int in1L, int in2L, int pwmR, int in1R, int in2R) {
    _pwmL = pwmL; _in1L = in1L; _in2L = in2L;
    _pwmR = pwmR; _in1R = in1R; _in2R = in2R;

    // Khởi tạo chân output
    pinMode(_in1L, OUTPUT);
    pinMode(_in2L, OUTPUT);
    pinMode(_in1R, OUTPUT);
    pinMode(_in2R, OUTPUT);

    // Khởi tạo kênh PWM
    _pwmChannelL = 0;
    _pwmChannelR = 1;
    ledcSetup(_pwmChannelL, freq, resolution);
    ledcAttachPin(_pwmL, _pwmChannelL);
    ledcSetup(_pwmChannelR, freq, resolution);
    ledcAttachPin(_pwmR, _pwmChannelR);
}

void motor::motorControl(int pwmChannel, int in1, int in2, int speed, bool way) {
    if (speed == 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    } else if (way) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    } else {    
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    }
    ledcWrite(pwmChannel, speed);
}

void motor::drive(int speedL, int speedR, bool way) {
    motorControl(_pwmChannelL, _in1L, _in2L, speedL, way);
    motorControl(_pwmChannelR, _in1R, _in2R, speedR, way);
}

void motor::stop() {
    motorControl(_pwmChannelL, _in1L, _in2L, 0, true);
    motorControl(_pwmChannelR, _in1R, _in2R, 0, true);
}

void motor::motion(int speedL, int speedR) {
    drive(speedL, speedR, true);
}


float motor :: PID_control(float setValue, float readValue, uint32_t lastTimePID, float Kp, float Ki, float Kd)
{
    static float error = 0.0;
    static float deltaTime = 0.0;
    static float lastError = 0.0;
    static float integral = 0.0;
    static float derivative = 0.0;
    static float output = 0.0;
    
    deltaTime = (float) (millis() - lastTimePID) / 1000.0;
    
    error = setValue - readValue;
    integral += (error * deltaTime);
    integral = constrain (integral, -1000, 1000);
    derivative = (error - lastError) / deltaTime;

    output = (Kp * error) + (Ki * integral) + (Kd * derivative);
    lastError = error;
    Serial.print("Gia tri output cua PID_control: "); Serial.println(output);
    Serial.print("Gia tri output cua error: "); Serial.println(error);
    Serial.print("Gia tri output cua deltaTime: "); Serial.println(deltaTime);
    Serial.print("Gia tri output cua lastError: "); Serial.println(lastError);

    return output;
}

