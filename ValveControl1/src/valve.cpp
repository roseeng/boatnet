#include "Arduino.h"
#include "valve.h"

#define DIR_CLOSE FORWARD
#define DIR_OPEN BACKWARD

/// A simple encapsulation of the electirc valve.
/// The valve has a motor and two end position switches
/// This class keeps track of the current state.
/// You set a new state using Open() and Close(),
/// after that you need to call GetState (or GetStateString) in the main loop
/// this is where we monitor the end switches.

Valve::Valve(Adafruit_DCMotor* motor, int pin_open, int pin_closed)
{
    _motor = motor;
    _state = UNKNOWN;
    _pin_open = pin_open;
    _pin_closed = pin_closed;
}

MotorState Valve::GetState()
{
    bool sw_open = digitalRead(_pin_open) == 0;
    Serial.print(sw_open ? "Valve_Open True  " : "Valve_Open False ");
    if (_state == OPENING && sw_open)
    {
        _motor->run(RELEASE);
        _state = OPEN;
    }

    bool sw_closed = digitalRead(_pin_closed) == 0;
    Serial.println(sw_closed ? "Valve_Closed True " : "Valve_Closed False");
    if (_state == CLOSING && sw_closed)
    {
        _motor->run(RELEASE);
        _state = CLOSED;
    }

    return _state;
}

void Valve::Open()
{
    if (_state != OPEN) {
        _state = OPENING;
        _motor->run(DIR_OPEN);
    }
}

void Valve::Close()
{
    if (_state != CLOSED) {
        _state = CLOSING;
        _motor->run(DIR_CLOSE);
    }
}

const char* const Valve::GetStateStr()
{    
    switch (GetState())
    {
    case UNKNOWN:
        return "UNKNOWN";
    case OPEN:
        return "OPEN";
    case OPENING:
        return "OPENING";
    case CLOSED:
        return "CLOSED";
    case CLOSING:
        return "CLOSING";
    
    default:
        return "BAD VALUE";
    }
}

