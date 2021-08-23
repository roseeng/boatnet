#include "Arduino.h"
#include "valve.h"

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <LowPower.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);

// The end detection switches
#define PIN_VALVE_SW1 6
#define PIN_VALVE_SW2 7

Valve valve = Valve(motor1, PIN_VALVE_SW1, PIN_VALVE_SW2);

// Define the open-close switches on the dashboard
// A dpdt switch with spring return makes most sense
// For the interrupt version on an Uno, this has to be 2 and 3
#define PIN_DASH_SW1 2
#define PIN_DASH_SW2 3

void wakeUp()
{
    // Just a handler for the pin interrupt.
}

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);  
  Serial.println("Valve control V1 - Adafruit Motorshield V2 version with interrupts");

  pinMode(PIN_VALVE_SW1, INPUT_PULLUP);
  pinMode(PIN_VALVE_SW2, INPUT_PULLUP);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  motor1->setSpeed(255);
  
  pinMode(PIN_DASH_SW1, INPUT_PULLUP);
  pinMode(PIN_DASH_SW2, INPUT_PULLUP);
  
  Serial.print("State: ");
  Serial.println(valve.GetStateStr());
}

void loop()
{
  Serial.print("Valve state: ");
  Serial.println(valve.GetStateStr());   
  
  bool sw_open = digitalRead(PIN_DASH_SW1) == 0;
  if (sw_open) {
    Serial.println("Dash press: Open");
    valve.Open();
  }
  bool sw_close = digitalRead(PIN_DASH_SW2) == 0;
  if (sw_close) {
    Serial.println("Dash press: Close");
    valve.Close();
  }

  if (valve.GetState() == OPEN || valve.GetState() == CLOSED) {
    Serial.println("Going to sleep...");
    attachInterrupt(digitalPinToInterrupt(PIN_DASH_SW1), wakeUp, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_DASH_SW2), wakeUp, FALLING);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    detachInterrupt(digitalPinToInterrupt(PIN_DASH_SW1));
    detachInterrupt(digitalPinToInterrupt(PIN_DASH_SW2));
    Serial.println("Awake again!");
  }
}

