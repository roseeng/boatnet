#ifndef Valve_h
#define Valve_h

#include "Arduino.h"

#include <Wire.h>
#include <Adafruit_MotorShield.h>

enum MotorState {
  UNKNOWN,
  OPEN,
  OPENING,
  CLOSED,
  CLOSING
};

class Valve
{
    public:
        Valve(Adafruit_DCMotor* motor, int pin_open, int pin_closed);
        MotorState GetState();
        const char* const GetStateStr();
        void Open();
        void Close();
    private:
        Adafruit_DCMotor* _motor;
        MotorState _state;
        int _pin_open;
        int _pin_closed;
};

#endif
