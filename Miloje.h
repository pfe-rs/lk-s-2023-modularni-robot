
#ifndef CustomLED_h
#define CustomLED_h

#include <Arduino.h>
#include <AccelStepper.h>
#include <ez_SIPO8_lib.h>
#include <Servo.h>
#define max_SIPOs  1
#define max_timers 0


void PinSetter(int dp1, int sp1, int dp2, int sp2, int servoDown, int servoUP, int Ultra);

class Miloje {
  public:
    Miloje(int sp1, int dp1, int sp2, int dp2);
    void Forward(int obrt, int sped);
    void Forward_angle(int angle, int sped);
    void Spin(int angle);
    void Curve(float angle, int sped, int d);


  private:
    int step_pin1;
    int dir_pin1;
    int step_pin2;
    int dir_pin2;



};

class Pan_tilt {
  public:
    Pan_tilt(int pin1, int pin2);
    void Cross();
    void SetMe(int pos_down, int pos_up);
    float UltraSonic(int trig_pin);


  private:
    int pup;
    int pdown;
    Servo ServoUP;
    Servo ServoDown;
};

class EightBit {
  public:
    EightBit() : my_SIPOs(max_SIPOs, max_timers) {}
    void Setup();
    void Ctrl(int pin, int state);
    void SetEmAll(int *niz);


  private:
    int states[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    SIPO8 my_SIPOs;
    int bank_id;
};
class Comu {
  public:
    Comu();
    void SERIAL_READ();
    void DecodeTYPE(String *strs);
    void DecodeM(String *strs);
    void DecodeS(String *strs);
    void DServo(String *strs);
    void DStepper(String *strs);
    void Send(String *strings, int who);
    void BT();
    void Setup();
  private:
};

#endif
