#include "Miloje.h"
#include <AccelStepper.h>
#include <Servo.h>

Miloje::Miloje(int sp1,int dp1,int sp2,int dp2) {
  step_pin1 = sp1;
  dir_pin1 = dp1;
  step_pin2 = sp2;
  dir_pin2 = dp2;
}

void Miloje::pravo(int obrt,int sped) {
  AccelStepper stepper1(AccelStepper::DRIVER, step_pin1, dir_pin1);
  stepper1.setMaxSpeed(sped);
  stepper1.setAcceleration(1000.0);
  stepper1.move(obrt*210);
  stepper1.runToPosition();
 
}
Pan_tilt::Pan_tilt(int p1,int p2) 
{
  pdown=p1;
  pup=p2;
}
void Pan_tilt::Cross(){
  Servo ServoUP;
  Servo ServoDown;
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

void Pan_tilt::SetMe(int pos_down){
  Servo ServoUP;
  Servo ServoDown;
  ServoUP.attach(pup);  
  ServoDown.attach(pdown);
  ServoDown.write(pos_down);
  
  
  
}
