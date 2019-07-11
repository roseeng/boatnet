/*

Control a motor using a Sparkfun TB6612FNG H-Bridge
2019 Göran Roseen

Based on SparkFun_TB6612.h (https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library/blob/master/src/SparkFun_TB6612.h)
Michelle @ SparkFun Electronics

*/

#ifndef motor_h
#define motor_h

#include <Arduino.h>

//used in some functions so you don't have to send a speed
#define DEFAULTSPEED 255  

class Motor
{
  public:
    // Constructor. Mainly sets up pins.
    Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin);      

    // Drive in direction given by sign, at speed given by magnitude of the 
  //parameter.
    void drive(int speed);  
  
  // drive(), but with a delay(duration)
    void drive(int speed, int duration);  
  
  //currently not implemented
    //void stop();           // Stop motors, but allow them to coast to a halt.
    //void coast();          // Stop motors, but allow them to coast to a halt.
  
  //Stops motor by setting both input pins high
    void brake(); 
  
  //set the chip to standby mode.  The drive function takes it out of standby 
  //(forward, back, left, and right all call drive)
  void standby(); 
  
  private:
    //variables for the 2 inputs, PWM input, Offset value, and the Standby pin
  int In1, In2, PWM, Offset,Standby;
  
  //private functions that spin the motor CC and CCW
  void fwd(int speed);
  void rev(int speed);

};


#endif
