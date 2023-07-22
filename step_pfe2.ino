#include "Miloje.h"

const int STEPS_PER_REVOLUTION = 200; // Change this based on your motor's specification

const int STEP_PIN = 8;
const int DIR_PIN = 9;
Miloje M1(11,12,7 ,6);
Pan_tilt T1(10,9);//donji pa gornji
EightBit J1;
Comu COM1;


void setup() {
  //Serial.begin(9600);
  J1.Setup();
  PinSetter(11,12,7 ,6,10,9,13);//dir1,step1,dir2,,step2,servo1,servo2,ultra
}

void loop() {
  //M1.pravo(1,2000);
  delay(400);
  //int niz[8]={0,1,0,1,0,1,1,0};
  //J1.SetEmAll(niz);
  COM1.SERIAL_READ();
    
  
  

  //T1.SetMe(100,20);
  //T1.Cross();
  //float raz=T1.UltraSonic(13);//triger
  //Serial.println(raz);
  
  //J1.Ctrl(0,1);
 
}
