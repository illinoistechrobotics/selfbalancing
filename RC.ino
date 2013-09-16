int c=0;
char buf[4];
char in;
void sercomm(){
  in = Serial.read();
if(Serial.available()){
  if(in =='\n'){
    c=0;
  } else {
    buf[c]=in;
    c++;
  }
  if(c==2){
    memcpy(&ctl,buf,2);
  }
}
ctl=map(ctl,-32768,32767,-5,5);

}
