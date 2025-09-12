#ifndef motor_H
#define motor_H

#include <Arduino.h>
 extern int _pwmL, _in1L, _in2L;
   extern  int _pwmR, _in1R, _in2R;
    extern int _pwmChannelL, _pwmChannelR;
    
class motor{
    public: 
    motor(int pwmL, int in1L, int in2L, int pwmR, int in1R, int in2R);
    void drive(int speedL, int speedR, bool forward);
    void stop();
    void motion(int speedL, int speedR);
    
   void backward(int speedL, int speedR);
    void motorControl(int pwmChannel, int in1, int in2, int speed, bool forward);

    float PID_control(float setValue, float readValue, uint32_t lastTimePID, float Kp, float Ki, float Kd); // readValue là thông số đọc được từ ir 3 - > 12; 15, 16
    
    private : 
    float Kp, Ki, Kd;

};
#endif