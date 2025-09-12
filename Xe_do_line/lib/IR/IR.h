#ifndef IR_H
#define IR_H
#include <Arduino.h>
extern int s0;
extern int s1;
extern int s2;
extern int s3;
//extern int _led;
extern int SIG_pin;

// extern int IR_3L, IR_4L, IR_5L, IR_6L;
// extern int IR_7C, IR_8C, IR_15C, IR_16C; 
// extern int IR_9R, IR_10R, IR_11R, IR_12R;

extern int led[];
extern int black_data[];
extern int white_data[];

extern int data[];
class IR
{
  public:
  static void init(); // hàm khởi tạo các chân 4067
  static void display(); // in ra gia tri 16 mat line
  static int readMux(int channel); // tra ve gia tri cua tung led 0 - > 16
  static int detectedline(); // xe vẫn nằm trên line 
  static int aver(int channel); // hàm đọc từng ir1 10 lần rồi trả về giá trị trung bình
  // giá trị trả về 0 hoặc 1 của từng mắt ir trên line
  static int ir_1L();
  static int ir_2L();
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
  static int ir_13R();
  static int ir_14R(); 
  // giá trị trả về 0 hoặc 1 của từng mắt ir trên line

  static int value_ss(int k); // tạo giá trị so sánh cho các led
  static void  read_black_line(); // hàm đọc line trắng cho 16 ir 
  static void  read_white_line(); // hàm đọc line đen cho 16 ir
  static void  write_information(int STT); // STT là ir thứ STT
  static void print_line(); // hàm in line đọc được từ 16ir
  static int fullwhiteline(); // nếu ir đọc toàn màu trắng nó sẽ trả về 1

  void read_line();
  
};

#endif