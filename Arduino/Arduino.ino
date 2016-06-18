#include <Servo.h>

uint8_t _servoPins[8] = {A8,A10,A12,A14,A9,A11,A13,A15};

Servo servos[8] = {Servo(),Servo(),Servo(),Servo(),Servo(),Servo(),Servo(),Servo()};
String received = "";
int releaseAngle = 55;
int holdAngle = 105;
int actionTime = 300;
int motionTime = 300;
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  delay(100);
  enableServos();
}
void disableServos(){
  for(uint8_t i=0;i<8;i++){
    servos[i].detach();
  }
}
void enableServos(){
  for(uint8_t i=0;i<8;i++){
    servos[i].attach(_servoPins[i]);
    servos[i].write(i<4?90:releaseAngle);
    delay(motionTime-100);
  }
  delay(motionTime);
  servos[0].write(90);
  delay(motionTime);
  servos[1].write(90);
  delay(motionTime);
  servos[2].write(90);
  delay(motionTime);
  servos[3].write(90);
  delay(motionTime);
}
void flipX(int dir){
  releaseY();
  delay(motionTime);
  servos[1].write(0);
  servos[3].write(180);
  delay(motionTime+200);
  holdX();
  delay(motionTime);
  if(dir==1){
    servos[0].write(0);
    servos[2].write(180);
  }else{
    servos[0].write(180);
    servos[2].write(0);
  }
  delay(motionTime+200);
  holdY();
  delay(motionTime);
  releaseX();
  delay(motionTime);
  servos[0].write(90);
  servos[2].write(90);
  delay(motionTime+200);
  holdX();
  delay(motionTime);
  releaseY();
  delay(motionTime);
  servos[1].write(90);
  servos[3].write(90);
  delay(motionTime+200);
  holdY();
  delay(motionTime);
}
void holdX(){
  servos[4].write(holdAngle-4);
  servos[6].write(holdAngle+4);
}
void releaseX(){
  servos[4].write(releaseAngle);
  servos[6].write(releaseAngle);
}

void flipY(int dir){
  releaseX();
  delay(motionTime);
  holdY();
  delay(motionTime);
  if(dir==1){
    servos[1].write(0);
    servos[3].write(180);
  }else{
    servos[1].write(180);
    servos[3].write(0);
  }
  delay(motionTime+200);
  holdX();
  delay(motionTime);
  releaseY();
  delay(motionTime);
  servos[1].write(90);
  servos[3].write(90);
  delay(motionTime+200);
  holdY();
  delay(motionTime);
}
void holdY(){
  servos[5].write(holdAngle-4);
  servos[7].write(holdAngle+4);
}
void releaseY(){
  servos[5].write(releaseAngle);
  servos[7].write(releaseAngle);
}
void rotateX(int dir,int face){
  int count = dir>0?dir:-dir;
  holdX();
  delay(motionTime);
  releaseY();
  delay(motionTime);
  servos[1].write(0);
  servos[3].write(180);
  delay(motionTime+100);
  for(int i=0;i<count;i++){
    holdY();
    delay(motionTime);
    servos[face==1?0:2].write(dir>0?180:0);
    delay(motionTime+300);
    servos[face==1?4:6].write(releaseAngle);
    delay(motionTime+100);
    servos[face==1?0:2].write(90);
    delay(motionTime+100);
    holdX();
    delay(motionTime);
  }
  servos[face==1?0:2].write(dir>0?102:76);
  delay(motionTime);
  servos[face==1?0:2].write(90);
  delay(motionTime);
  releaseY();
  delay(motionTime);
  servos[1].write(90);
  servos[3].write(90);
  delay(motionTime);
  holdY();
  delay(motionTime);
}
void rotateY(int dir,int face){
  int count = dir>0?dir:-dir;
  holdX();
  holdY();
  delay(motionTime);
  for(int i=0;i<count;i++){
    servos[face==1?1:3].write(dir>0?180:0);
    delay(motionTime+300);
    servos[face==1?5:7].write(releaseAngle);
    delay(motionTime+100);
    servos[face==1?1:3].write(90);
    delay(motionTime+300);
    holdY();
    delay(motionTime);
  }
  servos[face==1?1:3].write(dir>0?102:75);
  delay(motionTime);
  servos[face==1?1:3].write(90);
  delay(motionTime);
}
void loop() {
 if(Serial.available()){
    char c = Serial.read();
    if(c=='\n'){
      parseCommand();
      received="";
    }else{
      received+=c;
    }
  }
}
void parseCommand() {
  received.toLowerCase();
  char m_cmd = received.substring(0, 1).charAt(0);
  int s_cmd = received.substring(1,2).toInt();
  int v_cmd = received.substring(4).toInt();
  
  if(m_cmd=='m'){
    if(s_cmd==1){
      int count = v_cmd>0?v_cmd:-v_cmd;
      for(int i=0;i<count;i++){
        flipX(v_cmd>0?1:-1);
      }
    }else if(s_cmd==2){
      int count = v_cmd>0?v_cmd:-v_cmd;
      for(int i=0;i<count;i++){
        flipY(v_cmd>0?1:-1);
      }
    }else if(s_cmd==3){
      v_cmd==1?holdX():holdY();
    }else if(s_cmd==4){
      v_cmd==1?releaseX():releaseY();
    }else if(s_cmd==5){
      rotateX(v_cmd,1);
    }else if(s_cmd==6){
      rotateX(v_cmd,-1);
    }else if(s_cmd==7){
      rotateY(v_cmd,1);
    }else if(s_cmd==8){
      rotateY(v_cmd,-1);
    }
  }
  Serial.println("ok");
}
