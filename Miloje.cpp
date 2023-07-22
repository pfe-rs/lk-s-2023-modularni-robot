#include "Miloje.h"
#include <AccelStepper.h>
#include <Servo.h>

int ex_dir1,ex_dir2,ex_step_p1,ex_step_p2;
int ex_servo1,ex_servo2;//donji pa gornji
int ex_ultra;


int SensorRAW(int pin){
  return analogRead(pin);
}

void PinSetter(int dp1,int sp1,int dp2,int sp2,int servoDown,int servoUP,int Ultra){
  ex_dir1=dp1;
  ex_dir2=dp2;
  ex_step_p1=sp1;
  ex_step_p2=sp2;
  ex_servo1=servoDown;
  ex_servo2=servoUP;
  ex_ultra=Ultra; 
  }


Miloje::Miloje(int sp1,int dp1,int sp2,int dp2) {
  step_pin1 = sp1;
  dir_pin1 = dp1;
  step_pin2 = sp2;
  dir_pin2 = dp2;
  

}
Comu::Comu(){;}
void Comu::DServo(String *strs){
  Pan_tilt T1(ex_servo1,ex_servo2);
  if(strs[2]=="10"){
    T1.Cross();
  }

  else if(strs[2]=="11"){
    int par1=strs[3].toInt();
    int par2=strs[4].toInt();
    T1.SetMe(par1,par2);
    }
}

void Comu::DStepper(String *strs){
  int par1=strs[3].toInt();
  int par2=strs[4].toInt();
  Miloje M1(11,12,7 ,6);
  if(strs[2]=="10")
    {
    M1.pravo(par1,par2);   
    }
    else if(strs[2]=="11"){
      M1.pravoStepeni(par1,par2);
      ;
      }
}

void Comu::DecodeM(String *strs){
  if(strs[1]=="S"){
    DServo(strs);
  }

  else if(strs[1]=="A"){
    DStepper(strs);
    }
}

void Comu::DecodeTYPE(String *strs){
  if(strs[0]=="M")
  {
    DecodeM(strs);
  }
  else if(strs[0]=="S")
  {
    ;
  }
  else{
    digitalWrite(7,1);
    
    }
}  
void Comu::Send(String *strings,int who){
  Serial.begin(9600);
  int i;
  String st="ydiyisy";
  Serial.println(st);
  for(i=0;i<sizeof(strings);i++)
  {
    String st="S"+strings[i];
    Serial.println(st);
    
  }

  
  }
void Comu::SERIAL_READ(){
  String str;
  Serial.begin(9600);
  String strs[20];
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    str = Serial.readString();
  }
//  st=str
//  Serial.close();
  int StringCount = 0;
  while (str.length() > 0)
  {
    int index = str.indexOf(' ');
    if (index == -1) // No space found
    {
      strs[StringCount++] = str;
      break;
    }
    else
    {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }
  DecodeTYPE(strs);
  Serial.println(strs[0]);
  
}
/////////////////////////////////////////////
void Miloje::pravo(int obrt,int sped) {
  AccelStepper stepper1(AccelStepper::DRIVER, step_pin1, dir_pin1);
  stepper1.setMaxSpeed(sped);
  stepper1.setAcceleration(1000.0);
  stepper1.move(obrt*210);
  stepper1.runToPosition();
}

void Miloje::pravoStepeni(int angle,int sped){
  AccelStepper stepper1(AccelStepper::DRIVER, step_pin1, dir_pin1);
  stepper1.setMaxSpeed(sped);
  stepper1.setAcceleration(1000.0);
  stepper1.move(angle*(210/360));
  stepper1.runToPosition();
  }
Pan_tilt::Pan_tilt(int p1,int p2) 
{
  pdown=p1;
  pup=p2;
  ex_servo1=pdown;
  ex_servo1=pup; 
}

void Pan_tilt::Cross(){
  ServoUP.attach(pup);  
  ServoDown.attach(pdown);
  int i,j;
  for(i=0;i<3;i++){
    ServoDown.write(i*90);
    for(j=0;j<3;j++)
    {
    ServoUP.write(j*40+100);
    delay(2000);
    }
   }  
}

void Pan_tilt::SetMe(int pos_down,int pos_up){
  ServoUP.attach(pup);  
  ServoDown.attach(pdown);
  ServoDown.write(pos_down);
  ServoUP.write(pos_up);
  delay(2000);
     
}
float Pan_tilt::UltraSonic(int trig_pin){
  #define trig trig_pin
  #define echo A0
  /*
  Pan_tilt T1(10,9);
  T1.SetMe(100,90);*/
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int t = pulseIn(echo, HIGH);
  float s=t*0.017;
  return s;
  }

void EightBit::Setup() {
  bank_id= my_SIPOs.create_bank(13, 7, 12, 1);
  my_SIPOs.set_all_array_pins(LOW); 
  my_SIPOs.xfer_array(MSBFIRST);
  delay(2000); 
}

void EightBit::SetEmAll(int *niz){
  int i;
  for(i=0;i<8;i++)
  {
  states[i]=niz[i];
  my_SIPOs.set_array_pin(i,states[i]);
  }
  
  my_SIPOs.xfer_array(MSBFIRST);
  }

void EightBit::Ctrl(int pin,int state){

  int i; 
  states[pin]=state;
  for(i=0;i<8;i++)
  {
  my_SIPOs.set_array_pin(i,states[i]);
  }
  my_SIPOs.xfer_array(MSBFIRST);
  delay(2000);
  
  }
  
