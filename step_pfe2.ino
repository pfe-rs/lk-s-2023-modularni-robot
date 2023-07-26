#include "Miloje.h"

Pan_tilt T1(10,9);//donji pa gornji
EightBit J1;
Comu COM1;
Miloje M1(11,50,12,51);

void setup() {
  //Serial.begin(9600);
  //J1.Setup();
  //PinSetter(11,12,7 ,6,10,9,13);//dir1,step1,dir2,,step2,servo1,servo2,ultra
}

void loop() {
  //M1.pravo(2,500);
  M1.Kriva(30,200,20000);
  delay(20000);
 
}
