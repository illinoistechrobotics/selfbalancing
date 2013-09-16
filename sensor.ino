#define GYRO_ADDR 0x68
#define ACCEL_ADDR 0x53
// DEPENDS: Wire.h
void gyro_init(){
Wire.beginTransmission(GYRO_ADDR);
Wire.write(0x16);
Wire.write(0b00001010);
Wire.endTransmission();
}
void accel_init(){
Wire.beginTransmission(ACCEL_ADDR);
Wire.write(0x2d);
Wire.write(0x08);
Wire.endTransmission();
}
float read_gyro(char axis){
float out=0.0;
float offset=0.0;
uint8_t hb,lb;
int dout;
Wire.beginTransmission(GYRO_ADDR);
switch(axis){
case 'x':
Wire.write(0x1d);
break;
case 'y':
Wire.write(0x1f);
offset=-5;
break;
case 'z':
Wire.write(0x21);
offset=2.7;
break;
}
Wire.endTransmission();
Wire.beginTransmission(GYRO_ADDR);
Wire.requestFrom(GYRO_ADDR,2);
hb=Wire.read();
lb=Wire.read();
dout=(hb<<8)|lb;
out=(float)dout/14.375;
Wire.endTransmission();
return out+offset;
}
float read_accel(char axis){
float out=0.0;
uint8_t hb,lb;
int dout;
Wire.beginTransmission(ACCEL_ADDR);
switch(axis){
case 'x':
Wire.write(0x32);
break;
case 'y':
Wire.write(0x34);
break;
case 'z':
Wire.write(0x36);
break;
}
Wire.endTransmission();
Wire.beginTransmission(ACCEL_ADDR);
Wire.requestFrom(ACCEL_ADDR,2);
lb=Wire.read();
hb=Wire.read();
dout=(hb<<8)|lb;
out=(float)dout*0.00390625;
Wire.endTransmission();
return out;
}
