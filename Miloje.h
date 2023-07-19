#ifndef CustomLED_h
#define CustomLED_h

#include <Arduino.h>
#include <AccelStepper.h>
class Miloje {
public:
  Miloje(int sp1,int dp1,int sp2,int dp2);
  void pravo(int obrt,int sped);



private:
  int step_pin1;
  int dir_pin1;
  int step_pin2;
  int dir_pin2;
  

};

class Pan_tilt{
public:
  Pan_tilt(int pin1,int pin2);
  void Cross();
  void SetMe(int pos_down);

private:
  int pup;
  int pdown;
};

#endif
