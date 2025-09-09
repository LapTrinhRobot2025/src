#include "IR.h"
//Mux control pins
int s0 = 4;
int s1 = 19;
int s2 = 18;
int s3 = 5;

//Mux in "SIG" pin
int SIG_pin = 34;

// int IR_3L, IR_4L, IR_5L, IR_6L;
// int IR_7C, IR_8C, IR_15C, IR_16C; 
// int IR_9R, IR_10R, IR_11R, IR_12R;

int black_data[20] = {0}; // lưu giá trị so sánh của 12 led 
int white_data[20] = {0};
int led[] = {3, 4, 5, 6, 7, 8, 15, 16, 9, 10, 11, 12};
void IR :: init(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);


}


void IR :: display() 
{

  for(int i = 0; i < 16; i ++){          
    Serial.print(readMux(i));
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);
}
int IR :: readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 1
    {1,0,0,0}, //channel 2
    {0,1,0,0}, //channel 3
    {1,1,0,0}, //channel 4
    {0,0,1,0}, //channel 5
    {1,0,1,0}, //channel 6
    {0,1,1,0}, //channel 7
    {1,1,1,0}, //channel 8
    {0,0,0,1}, //channel 9
    {1,0,0,1}, //channel 10
    {0,1,0,1}, //channel 11
    {1,1,0,1}, //channel 12
    {0,0,1,1}, //channel 13
    {1,0,1,1}, //channel 14
    {0,1,1,1}, //channel 15
    {1,1,1,1}  //channel 16  
  };

  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel - 1][i]);
  }
  int val = analogRead(SIG_pin); 
  return val;
}

int IR :: detectedline()
{
  if(ir_7C() && ir_8C() && ir_15C() && ir_16C()) return 1; // void forward();
  else return 0; // xe bi lech huong
}
int IR :: aver(int n) // hàm trả về giá trị trung bình 10 lần đọc của mỗi led
{
  int sum = 0;
  for(int i = 0; i < 5; i++)  sum += readMux(n);
  sum /= 5;
  int value = map(sum, 0, 4095, 0, 755);
  return value;
}

void IR :: read_black_line()
{  
  Serial.println("Preparing read black line.");
  delay(2000);
  for(int i = 0; i < 12; i++)
  {
    black_data[led[i]] += aver(led[i]);
    delay(100);
  }
  
  Serial.println("Done read black line!");
  delay(5000);
}

void IR :: read_white_line()
{
  Serial.println("Preparing read white line.");
  delay(2000);
  for(int i = 0; i < 12; i++)
  {
    white_data[led[i]] += aver(led[i]);
     delay(100);
  }
   
  Serial.println("Done read white line!");
  delay(5000);
}

int IR :: value_ss(int k)
{
  return (white_data[k] + black_data[k]) / 2;
}
// trả về giá trị của các led 
int IR :: ir_3L() {return aver(3) > value_ss(3) ? 1 : 0;}
int IR :: ir_4L() {return aver(4) > value_ss(4) ? 1 : 0;}
int IR :: ir_5L() {return aver(5) > value_ss(5) ? 1 : 0;}
int IR :: ir_6L() {return aver(6) > value_ss(6) ? 1 : 0;}

int IR :: ir_7C() {return aver(7) > value_ss(7) ? 1 : 0;}
int IR :: ir_8C() {return aver(8) > value_ss(8) ? 1 : 0;}
int IR :: ir_15C() {return aver(15) > value_ss(15) ? 1 : 0;}
int IR :: ir_16C() {return aver(16) > value_ss(16) ? 1 : 0;}

int IR :: ir_9R() {return aver(9) > value_ss(9) ? 1 : 0;}
int IR :: ir_10R() {return aver(10) > value_ss(10) ? 1 : 0;}
int IR :: ir_11R() {return aver(11) > value_ss(11) ? 1 : 0;}
int IR :: ir_12R() {return aver(12) > value_ss(12) ? 1 : 0;}
// trả về giá trị của các led

void IR :: write_information(int STT, int array)
{
  int _value = aver(STT);
  int _value_led = aver(led[array]);
  int _value_ss_ = value_ss(STT);
  int _value_ss_led = value_ss(led[array]);

  Serial.print("Gia tri trung binh: "); Serial.println(_value);
  Serial.print("Gia tri trung binh led thu 3: "); Serial.println(_value_led);
  Serial.print("Gia tri doc line trang: "); Serial.println(white_data[STT]);
  Serial.print("Gia tri doc line den: "); Serial.println(black_data[STT]);
  Serial.print("Gia tri so sanh: "); Serial.println(_value_ss_);
  Serial.print("Gia tri so sanh led thu 3: "); Serial.println(_value_ss_led);
}

void IR :: write_line()
{
 Serial.print(ir_3L()); Serial.print(" | ");
  Serial.print(ir_4L()); Serial.print(" | ");
  Serial.print(ir_5L()); Serial.print(" | ");
  Serial.print(ir_6L()); Serial.print(" | ");
  Serial.print(ir_7C()); Serial.print(" | ");
  Serial.print(ir_8C()); Serial.print(" | ");
  Serial.print(ir_15C()); Serial.print(" | ");
  Serial.print(ir_16C()); Serial.print(" | ");
  Serial.print(ir_9R()); Serial.print(" | ");
  Serial.print(ir_10R()); Serial.print(" | ");
  Serial.print(ir_11R()); Serial.print(" | ");
  Serial.print(ir_12R()); Serial.print(" | ");
}
