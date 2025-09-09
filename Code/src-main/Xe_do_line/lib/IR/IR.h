#ifndef IR_H
#define IR_H
#include <Arduino.h>
extern int s0;
extern int s1;
extern int s2;
extern int s3;
extern int SIG_pin;

// extern int IR_3L, IR_4L, IR_5L, IR_6L;
// extern int IR_7C, IR_8C, IR_15C, IR_16C; 
// extern int IR_9R, IR_10R, IR_11R, IR_12R;

extern int led[];
extern int black_data[];
extern int white_data[];
class IR
{
  public:
  static void init();
  static void display(); // in ra gia tri 16 mat line
  static int readMux(int channel); // tra ve gia tri cua tung led 0 - > 16
  static int detectedline(); // xe vẫn nằm trên line 
  static int aver(int channel);

  // giá trị trả về 0 hoặc 1 của từng mắt ir trên line
  static int ir_3L(); 
  static int ir_4L(); 
  static int ir_5L();
  static int ir_6L(); 
  static int ir_7C();
  static int ir_8C(); 
  static int ir_15C();
  static int ir_16C(); 
  static int ir_9R();
  static int ir_10R(); 
  static int ir_11R();
  static int ir_12R(); 
  // giá trị trả về 0 hoặc 1 của từng mắt ir trên line

  static int value_ss(int k);
  static void  read_black_line(); // ham lấy giá trị so sánh line trắng 
  static void  read_white_line(); // hàm lấy giá trị so sánh line đen
  static void  write_information(int STT); // STT là ir thứ STT
  static void write_line(); // đọc giá trị của ir trên line

  static int  IR_56();
  static int  IR_34();
  static int  IR_910();
  static int  IR_1112();
  static uint8_t value_line(); // hàm trả về giá trị line, dùng để dò line
};
#endif