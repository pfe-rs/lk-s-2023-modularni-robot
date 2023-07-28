#include "Miloje.h"

//Pan_tilt T1(10,9);//donji pa gornji
//EightBit J1;
Comu COM1;
Miloje M1(11,50,12,51);

void setup() {
  PinSetter(50,11,51,12,2,3,23);//dir1,step1,dir2,,step2,servo1,servo2,ultra
  COM1.Setup();
}

void loop() 
{
  //M1.Forward(2,300);
  COM1.BT();
  //COM1.SERIAL_READ();
  delay(2000);
}
