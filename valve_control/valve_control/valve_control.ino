/*

valve_control - open and close the electric valve in the boat (Självläns).

The valve needs +12V/-12V on the control lines, so we are using a motor controller. At the same time
we can give the output a PWM ramp to get a nice, non-yanky, driving of the motor.
The valve has 5 lines, 2 for the motor, 2 for the end detection switches and a common ground for the switches.

Step 1 is to simply open and close the valve.
Step 2 is controlling the feather using 2 digital inputs.
Step 3 is controlling the feather using BLE.
Step 4 is communicating open/close status to a future dashboard control node.

Using Adafruit nrf52 - https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/introduction

Add board manager URL https://www.adafruit.com/package_adafruit_index.json
Add board 'Adafruit nRF52 by Adafruit'
Select 'Adafruit Bluefruit nRF52832 Feather' (for the nRF52 Feather) from the Tools -> Board menu

The valve is controlled by a Sparkfun motor driver - https://www.sparkfun.com/products/14451
For that, we could be using the TB6612FNG library at https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library/archive/master.zip
But perhaps it simple enough to just write the code for one motor.
 
*/

#include "motor.h"

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

#define offset 1

Motor motor = Motor(AIN1, AIN2, PWMA, offset, STBY);

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.standby();
}
