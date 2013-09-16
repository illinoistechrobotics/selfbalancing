#include <Servo.h>

#include <Wire.h>
/*
#define _A1 6
#define _A2 7
#define _B1 8
#define _B2 9
*/
#define _PWMA 10
#define _PWMB 11
//#define _STBY 12

Servo m1;
Servo m2;
float setpoint=0;
int drive;
boolean sign=false;
const float P=12.0;
const float I=120.0;
const float D=0.1;
const float A=0.93;
float a=A;
const int bufferlen=4;
float error;
int ctl=10;
float powerint=0;
void setup(){
  Wire.begin();
  m1.attach(10);
  m2.attach(11);
  gyro_init();
  accel_init();
  Serial.begin(57600);
 // Serial.begin(115200);
 /*
  pinMode(_A1, OUTPUT);
  pinMode(_A2, OUTPUT);
  pinMode(_B1, OUTPUT);
  pinMode(_B2, OUTPUT);
  pinMode(_PWMA, OUTPUT);
  pinMode(_PWMB, OUTPUT);
  pinMode(_STBY, OUTPUT);
  digitalWrite(_STBY,HIGH);
  */
}
void STOP(){
  //driveMotors(0,1);
 //driveMotors(0,0);
}
void loop(){
// Serial.println(angle_accel());
//Serial.println(read_gyro('y'));

drive=(int)evalPID();
powerint=((drive*(dtc()/800))+powerint);
if(powerint<-5)
powerint=-5;
if(powerint>5)
powerint=5;
setpoint=ctl;
//setpoint=0;
sercomm();
if((drive>=0&&(!sign))||(drive<0&&sign)||drive<-200||drive>200){
  powerint=0;
} 
if(drive>=0){
  sign=false;
} else{
  sign=true;
}
  
if(drive<0.0)
drive=drive-30;
if(drive>0.0)
drive=drive+30;
  m2.writeMicroseconds(1500-constrain(drive,-500,500));
  m1.writeMicroseconds(1500-constrain(drive,-500,500));
}
/*
void driveMotors(int power, int motor){
  power=constrain(power,-255,255);
  if(motor==0){
    if(power==0){
      digitalWrite(_A1,LOW);
      digitalWrite(_A2,LOW);
      digitalWrite(_PWMA,LOW);
    } else {
      if(power<0){
        digitalWrite(_A1,LOW);
      digitalWrite(_A2,HIGH);
      } else {
        digitalWrite(_A1,HIGH);
      digitalWrite(_A2,LOW);
      }
      analogWrite(_PWMA,abs(power));
    } 
    }
  else{
    if(power==0){
      digitalWrite(_B1,LOW);
      digitalWrite(_B2,LOW);
      digitalWrite(_PWMB,LOW);
    } else {
      if(power<0){
        digitalWrite(_B1,LOW);
      digitalWrite(_B2,HIGH);
      } else {
        digitalWrite(_B1,HIGH);
      digitalWrite(_B2,LOW);
      }
      analogWrite(_PWMB,abs(power));
    } 
    
  }
  
}
*/


