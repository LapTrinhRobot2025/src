#include "IR.h"
#include "motor.h"
#include <Arduino.h>

#define PWML 13
#define in1L 14
#define in2L 12
#define PWMR 32
#define in1R 26
#define in2R 25

#define LED 27

// parameter of PID
float Kp = 0.3;
float Ki = 0.1;
float Kd = 0.1;
float setpoint = 250;
uint32_t lastTimePID = 0.0;
float PID_outPut = 0.0;
// parameter of PID

int speed = 250;
motor robot(PWML, in1L, in2L, PWMR, in1R, in2R);
IR IRline;

void blink(){
  // nháy LED, nhấp nháy đến khi touch
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  //QB
}

void takeline(){
  // lấy mẫu line
  Serial.println("Taking lines started!!");   
  pinMode(LED, OUTPUT);
  while (touchRead(4) > 20) blink();
  IRline.read_black_line();

  while (touchRead(4) > 20) blink();
  IRline.read_white_line();

  while (touchRead(4) > 20) blink();
  Serial.println("Take lines done!");
  //QB
}

void setup() {
  Serial.begin(115200);
  IRline.init();
  // đọc giá trị line trắng và đen để tạo giá trị so sánh 
  takeline();
  // đọc giá trị line trắng và đen để tạo giá trị so sánh 

  // IRline.write_information(16); // in giá trị so sánh và giá trị của 1 IRline cụ thể
}


float PID_value()
{
  float readValue = 0.0;
  if(IRline.detectedline()) readValue = 0.0;
  if(IRline.detectedline() && (IRline.IR_56() || IRline.IR_910())) readValue = 50.0;
  if(IRline.detectedline() && (IRline.IR_34() || IRline.IR_1112())) readValue = 150.0;
    float sp = robot.PID_control(setpoint, readValue, lastTimePID, Kp, Ki, Kd);
  return sp;
}

void followline()
{
  int PID = PID_value();
  int lsp = speed - PID;
  int rsp = speed + PID;

  if (lsp > 250) {
    lsp = 250;
  }
  if (lsp < 0) {
    lsp = 0;
  }
  if (rsp > 250) {
    rsp = 250;
  }
  if (rsp < 0) {
    rsp = 0;
  }
  robot.motion(lsp, rsp);
}



void loop() {
  robot.motion(255, 255);
}