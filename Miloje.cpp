#include "Miloje.h"
#include <AccelStepper.h>
#include <Servo.h>
#include <ez_SIPO8_lib.h> 

int ex_dir1,ex_dir2,ex_step_p1,ex_step_p2;
int ex_servo1,ex_servo2;//donji pa gornji
int ex_ultra;

void PinSetter(int dp1,int sp1,int dp2,int sp2,int servoDown,int servoUP,int Ultra){
  ex_dir1=dp1;
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

Comu::Comu() {}

void Comu::Setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void Comu::DServo(String *strs){
  Pan_tilt T1(ex_servo1,ex_servo2);
  if(strs[2]=="10"){
    Serial.println("Cross ukljucen");
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
//  Serial1.println(isDigit(strs[4]));
  int par2=strs[4].toInt();
  Serial1.println(par2);
  Miloje M1(ex_step_p1,ex_dir1,ex_step_p2,ex_dir2);//int sp1,int dp1,int sp2,int dp2
  if(strs[2]=="10")
    {
    Serial1.print("Decoded right");
    Serial1.println(par1);
    Serial1.println(par2);
    M1.Forward(par1,par2);   
    }
  else if(strs[2]=="11"){
    M1.Forward_angle(par1,par2);
    }
  else if(strs[2]=="12"){
    M1.Spin(par1);
    }
 else if(strs[2]=="13"){
    float param1=strs[3].toFloat();
    int par3=strs[5].toInt();
    M1.Curve(param1,par2,par3);
    }
    
}

void Comu::DecodeM(String *strs){
  if(strs[1]=="S"){
    Serial1.println("USPEHH");
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


}
void Comu::BT(){
  String str;
  String strs[20];
  if (Serial1.available() > 0) {
    str = Serial1.readString();
    str = str.substring(0,str.length()+1);
    Serial1.println(str); 
  }
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

    Serial1.println(strs[0]);
    Serial1.println(strs[1]);
    Serial1.println(strs[2]);
    Serial1.println(strs[3]);
    Serial1.println("A"+strs[4]+"A");

  

  DecodeTYPE(strs);
}


void Comu::Send(String *strings,int who){
//  Serial.begin(9600);
  int i;
//  Serial.println(st);
  for(i=0;i<sizeof(strings);i++)
  {
    String st="S"+strings[i];
    Serial.println(st);
    
  }

  
  }
void Comu::SERIAL_READ(){
  String str;
//  Serial.begin(9600);
  String strs[20];
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    str = Serial.readString();
  }

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
    Serial.println(strs[0]);
    Serial.println(strs[1]);
    Serial.println(strs[2]);
    Serial.println(strs[3]);
    Serial.println(strs[4]);

  
  DecodeTYPE(strs);


  //Serial.println(strs[0]);
  
}

void Miloje::Curve(float angle,int sped,int d){//
    AccelStepper stepper1(AccelStepper::DRIVER, step_pin1, dir_pin1);
    AccelStepper stepper2(AccelStepper::DRIVER, step_pin2, dir_pin2);
    angle=angle*3.14/180;
    sped=sped*6;//brzina mm/s
    int L=225;//razmak medju tockovima
    float T=d/sped;//d je u mm ti se snadji s
    float omega=angle/T;
    float r=omega/sped;//radijus velikog kruga
    
  //  float V_right=omega*(r+L/2);
  // float V_left=omega*(r-L/2);

  float V_right=-(omega+2*sped)/2;
  float V_left=-(V_right-omega*r);
    
    int N_left=V_left/6;
    int N_right=V_right/6;
    
    stepper1.setMaxSpeed(V_right);
    stepper1.setAcceleration(200);
    stepper1.move(N_right);
    
    stepper2.setMaxSpeed(V_left);
    stepper2.setAcceleration(200);
    stepper2.move(N_left);  
    while((stepper1.distanceToGo() != 0)&&(stepper2.distanceToGo() != 0))
    {
      stepper1.run();
      stepper2.run();
    }
    stepper1.stop();
    stepper2.stop();
 






}
/////////////////////////////////////
void Miloje::Spin(int angle){
    int obrt=9/8*angle;
    AccelStepper stepper1(AccelStepper::DRIVER, step_pin1, dir_pin1);
    AccelStepper stepper2(AccelStepper::DRIVER, step_pin2, dir_pin2);
    int spido=500; 
    stepper1.setMaxSpeed(spido);
    stepper1.setAcceleration(200);
    stepper1.move(obrt);
    
    stepper2.setMaxSpeed(spido);
    stepper2.setAcceleration(200);
    stepper2.move(-obrt);   
    int i;
    while((stepper1.distanceToGo() != 0)&&(stepper2.distanceToGo() != 0)){
    stepper1.run();
    stepper2.run();
    }
      stepper1.stop();
  stepper2.stop();  
  }

void Miloje::Forward(int obrt,int sped) {
    AccelStepper stepper1(AccelStepper::DRIVER, step_pin1, dir_pin1);
    AccelStepper stepper2(AccelStepper::DRIVER, step_pin2, dir_pin2);
    sped=sped/5;
    obrt=-200*obrt;
    stepper1.setMaxSpeed(sped);
    stepper1.setAcceleration(800);
    stepper1.moveTo(obrt);
    
    stepper2.setMaxSpeed(sped);
    stepper2.setAcceleration(800);
    stepper2.moveTo(obrt);
    
  while((stepper1.distanceToGo() != 0)&&(stepper2.distanceToGo() != 0))
  {
    stepper1.run();
    stepper2.run();
  }
  stepper1.stop();
  stepper2.stop();

}

void Miloje::Forward_angle(int angle,int sped)
{
    int DRIVER;
    AccelStepper stepper1(AccelStepper::DRIVER, step_pin1, dir_pin1);
    AccelStepper stepper2(AccelStepper::DRIVER, step_pin2, dir_pin2);
    int obrt=-200*(angle/360);
    stepper1.setMaxSpeed(sped);
    stepper1.setAcceleration(800);
    stepper1.moveTo(obrt);
    
    stepper2.setMaxSpeed(sped);
    stepper2.setAcceleration(800);
    stepper2.moveTo(obrt);
  while((stepper1.distanceToGo() != 0)||(stepper2.distanceToGo() != 0)){
    stepper1.run();
    stepper2.run();
  }
  stepper1.stop();
  stepper2.stop();
  //stepper2.move(angle*(210/360));

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
  
