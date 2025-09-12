#include "IR.h"
#include "motor.h"
#include <Arduino.h>

#define PWML 13
#define in1L 14
#define in2L 12
#define PWMR 32
#define in1R 33
#define in2R 25

unsigned char last_turn = 0;
// parameter of PID
float Kp = 27;
float Ki = 1.2 * Kp * 0.1;
float Kd = 0.075 * Kp * 0.1;
float setpoint = 0.0;
uint32_t lastTimePID = 0.0;
float PID_outPut = 0.0;

int _led = 27; 
int _buzzer = 26;
int buz_channel = 0;
int touch = 4;
int rihgt_speed = 250;
int left_speed  = 250;

int dem = 0;

motor robot(PWML, in1L, in2L, PWMR, in1R, in2R);
IR IRline;

void blink(){
  // nháy __led, nhấp nháy đến khi touch
  digitalWrite(_led, HIGH);
  delay(100);
  digitalWrite(_led, LOW);
  delay(100);
  //QB
}

void takeline(){
  // lấy mẫu line
  Serial.println("Taking lines started!!");   
  pinMode(_led, OUTPUT);
  while (touchRead(4) > 20) blink();
  IRline.read_black_line();

  while (touchRead(4) > 20) blink();
  IRline.read_white_line();

  while (touchRead(4) > 20) blink();
  Serial.println("Take lines done!");
  //QB
}

// void takeline1(){
//   // lấy mẫu line
//   Serial.println("Taking lines started!!");   
//   pinMode(_led, OUTPUT);
//   while (touchRead(4) > 20) blink();
//   IRline.read_line();
//   Serial.println("Take lines done!");
//   //QB
// }

void setup()
{
    Serial.begin(115200);
    // Tên thiết bị Bluetooth
    pinMode(_led, OUTPUT);
    IRline.init();
    takeline();

    Serial.println("done init IR");
    ledcAttachPin(_buzzer, buz_channel);
    // gửi thông báo qua Bluetooth
}

void volume(){
    ledcWriteTone(buz_channel, 1000);
    delay(1000);
}

float PID_value()
{

    float readValue = 0.0;
    readValue = 0.6 * (IRline.ir_6L() - IRline.ir_9R()) + 1.2 * (IRline.ir_5L() - IRline.ir_10R()) + 3.1 * (IRline.ir_4L() - IRline.ir_11R()) + 4.3 * (IRline.ir_3L() - IRline.ir_12R()) + 5.5 * (IRline.ir_2L() - IRline.ir_13R()) + 6.6 * (IRline.ir_1L() - IRline.ir_14R());

    Serial.print("readValue: ");
    Serial.println(readValue);
    float sp = robot.PID_control(setpoint, readValue, lastTimePID, Kp, Ki, Kd);
    lastTimePID = millis();
    if (IRline.ir_1L() == 1) // line vuông góc vs xe bên phải
        last_turn = 1;

    else if (IRline.ir_14R() == 1)// line vuông góc vs xe bên trái
        last_turn = 2;
    return sp;
}

void followline() 
{
    float PID = PID_value();
    int lsp = (int)(left_speed - PID);
    int rsp = (int)(rihgt_speed + PID);

    if (lsp > left_speed)
    {
        lsp = left_speed;
    }
    if (lsp < 0)
    {
        lsp = 0;
    }
    if (rsp > rihgt_speed)
    {
        rsp = rihgt_speed;
    }
    if (rsp < 0)
    {
        rsp = 0;
    }
    
    // ý tưởng là tạo 1 biến lưu giá trị cũ của ir, nếu xe chạy ra khỏi line đen và all ir b ắt line trắng thì xe sẽ quay về bên last_turn trả về
    if (IRline.fullwhiteline() == 1) // nếu xe ra khỏi line đen -> all ir bắt line trắng thì sử dụng biến giá trị cũ điều khiển xe
    {
        if (last_turn == 1) 
        {
            lsp = left_speed;
            rsp = 50;
        }
        else if (last_turn == 2)
        {
            lsp = 50;

            rsp = rihgt_speed;
        }
    }
    Serial.print("lsp: ");   Serial.println(lsp);
    Serial.print("rsp: ");  Serial.println(rsp);
    robot.motion(lsp, rsp);
    Serial.println("activing!");
    //}
}
void loop()
{
    //  IR.write_information(6); // in giĂ¡ trá»‹ so sĂ¡nh vĂ  giĂ¡ trá»‹ cá»§a 1 ir cá»¥ thá»ƒ
    // hĂ m tráº£ vá» giĂ¡ trá»‹ nhá»‹ phĂ¢n 0 - 1 tÆ°Æ¡ng á»©ng vs tá»«ng máº¯t IR Ä‘ang náº±m trĂªn line tráº¯ng hoáº·c Ä‘en

    // robot.motion(250, 250);
    followline();
    // robot.motion(255,255);
}