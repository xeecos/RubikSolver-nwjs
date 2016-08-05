#include <Servo.h>

uint8_t _servoPins[8] = {A8,A10,A12,A14,A9,A11,A13,A15};

Servo servos[8] = {Servo(),Servo(),Servo(),Servo(),Servo(),Servo(),Servo(),Servo()};
String received = "";
float angles[8] = {90,90,90,90,90,90,90,90};
int releaseAngle = 55;
int holdAngle = 104;
int actionTime = 200;
int motionTime = 200;
void setup() {
  //disableServos();
  Serial.begin(115200);
  //Serial2.begin(115200);
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
    moveTo(i,i<4?90:releaseAngle);
    delay(motionTime-100);
  }
  delay(motionTime);
  moveTo(0,90);
  delay(motionTime);
  moveTo(1,90);
  delay(motionTime);
  moveTo(2,90);
  delay(motionTime);
  moveTo(3,90);
  delay(motionTime);
}
void flipX(int dir){
  releaseY();
  delay(motionTime);
  moveTo2(1,0,3,180);
  delay(motionTime+200);
  holdX();
  delay(motionTime);
  if(dir==1){
    moveTo2(0,0,2,180);
  }else{
    moveTo2(0,180,2,0);
  }
  delay(motionTime+200);
  holdY();
  delay(motionTime);
  releaseX();
  delay(motionTime);
  moveTo2(0,90,2,90);
  delay(motionTime+200);
  holdX();
  delay(motionTime);
  releaseY();
  delay(motionTime);
  moveTo2(1,90,3,90);
  delay(motionTime+200);
  holdY();
  delay(motionTime);
}
void holdX(){
  moveTo2(4,holdAngle-6-2,6,holdAngle+6-2);
}
void releaseX(){
  moveTo2(4,releaseAngle,6,releaseAngle);
}

void flipY(int dir){
  releaseX();
  delay(motionTime);
  holdY();
  delay(motionTime);
  if(dir==1){
    moveTo2(1,0,3,180);
  }else{
    moveTo2(1,180,3,0);
  }
  delay(motionTime+200);
  holdX();
  delay(motionTime);
  releaseY();
  delay(motionTime);
  moveTo2(1,90,3,90);
  delay(motionTime+200);
  holdY();
  delay(motionTime);
}
void holdY(){
  moveTo2(5,holdAngle-4+3,7,holdAngle+4+3);
}
void releaseY(){
  moveTo2(5,releaseAngle,7,releaseAngle);
}
void rotateX(int dir,int face){
  int count = dir>0?dir:-dir;
  holdX();
  delay(motionTime);
  releaseY();
  delay(motionTime);
  moveTo2(1,0,3,180);
  delay(motionTime+100);
  for(int i=0;i<count;i++){
    holdY();
    delay(motionTime);
    moveTo(face==1?0:2,dir>0?180:0);
    delay(motionTime+300);
    moveTo(face==1?4:6,releaseAngle);
    delay(motionTime+100);
    moveTo(face==1?0:2,90);
    delay(motionTime+100);
    holdX();
    delay(motionTime);
  }
  moveTo(face==1?0:2,dir>0?118:62);
  moveTo(face==1?0:2,dir>0?75:105);
  moveTo(face==1?0:2,90);
  delay(motionTime);
  releaseY();
  delay(motionTime);
  moveTo2(1,90,3,90);
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
    moveTo(face==1?1:3,dir>0?180:0);
    delay(motionTime+300);
    moveTo(face==1?5:7,releaseAngle);
    delay(motionTime+100);
    moveTo(face==1?1:3,90);
    delay(motionTime+300);
    holdY();
    delay(motionTime);
  }
  moveTo(face==1?1:3,dir>0?118:62);
  moveTo(face==1?1:3,dir>0?72:108);
  moveTo(face==1?1:3,90);
  delay(motionTime);
}
void moveTo(int pin,int angle){
  	int steps = 20;
    float stepAngle = (angle - angles[pin])/steps;
    int start = angles[pin]+stepAngle;
    for(int i=0;i<steps;i++){
      servos[pin].write(start+stepAngle*i);
      delay(abs(floor(stepAngle*6))+5);
    }
    delay(abs(floor(stepAngle*12))+50);
    angles[pin] = angle;
}
void moveTo2(int pin1,int angle1,int pin2,int angle2){
    int steps = 20;
    float stepAngle1 = (angle1 - angles[pin1])/steps;
    int start1 = angles[pin1]+stepAngle1;
    float stepAngle2 = (angle2 - angles[pin2])/steps;
    int start2 = angles[pin2]+stepAngle2;
    for(int i=0;i<steps;i++){
      servos[pin1].write(start1+stepAngle1*i);
      servos[pin2].write(start2+stepAngle2*i);
      delay(abs(floor(stepAngle1*6))+5);
    }
    delay(abs(floor(stepAngle1*12))+50);
    angles[pin1] = angle1;
    angles[pin2] = angle2;
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
    }else if(s_cmd==9){
      if(v_cmd==1){
        enableServos();
      }else{
        disableServos();
      }
    }
  }
  Serial.println("ok");
}
