
const float aof=-4.2;
float anglebuffer[bufferlen];
float errorint=0;
float lasterror=0;
float angleg=0;
float angb=0;
float lasttime= (float)micros();
float lasttimea= (float)micros();
float lasttimeb= (float)micros();
float lasttimec= (float)millis();
int i;

float dt(){
  float ret;
 ret=(float)micros()-lasttime;
 lasttime=(float)micros();
 return ret;
}
float dta(){
  float ret;
 ret=(float)micros()-lasttimea;
 lasttimea=(float)micros();
 return ret;
}
float dtb(){
  float ret;
 ret=(float)micros()-lasttimeb;
 lasttimeb=(float)micros();
 return ret;
}
float dtc(){
  float ret;
 ret=(float)millis()-lasttimec;
 lasttimec=(float)millis();
 return ret;
}
float angle_accel(){
  /*
 float a=(abs(read_accel('x')));
  if(a>1.0)
    a=1.0;
    float o=asin(a)*(180/PI)+4.2;
    if(read_accel('z')>-0.27){
    o=o*-1;
    }
    */
    float o;
    o=90-atan2(read_accel('x'),read_accel('z'))*(180/PI);
   // if(o>90)
    //o=90;
    //if(o<-90)
    //o=-90;
  return o+aof;
}

float angle_combined(){
  if(sqrt(pow(read_accel('x'),2)+pow(read_accel('z'),2))>1.7){
    a=1;
  }else{
    a=A;
  }
angb=a*(angb+((read_gyro('y')*dt()/1000000)))+(1-a)*angle_accel();
return angb;
}
void init_anglebuffer(){
  for(i=0;i<bufferlen;i++){
    anglebuffer[i]=angle_combined();
    delay(10);
  }
}
float read_anglebuffer(){
  float out;
  for(i=0;i<bufferlen;i++){
    out=out+anglebuffer[i];
  }
  return out/bufferlen;
  }
void update_anglebuffer(){
  for(i=0;i<bufferlen-1;i++){
    anglebuffer[i]=anglebuffer[i+1];
  } 
  anglebuffer[bufferlen-1]=angle_combined();
}
float evalPID(){
  float output;
  float derivterm;
  error=setpoint-read_anglebuffer();
  //if(abs(error)>40){
  ////Serial.println("EXCESS ANGLE KILL");
  //STOP();
  //}
 errorint=((error*(dta()/1000000))+errorint);
 if(errorint>10)
 errorint=5;
 if(errorint<-10)
 errorint=-5;
 derivterm=1000000*((error-lasterror)/(dtb()));
  output=(P*error)+(I*errorint)+(D*derivterm);
 // Serial.println(derivterm,10);
  update_anglebuffer();
  lasterror=error;
  return output;
}
