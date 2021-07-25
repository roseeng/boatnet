#include "Arduino.h"
#include "valve.h"

#include <Wire.h>
#include <Adafruit_MotorShield.h>

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

#define PIN_DASH_SW1 8
#define PIN_DASH_SW2 9

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);  
  Serial.println("Valve control V1 - Adafruit Motorshield V2 version");

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

int i = 1;

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

  delay(500);
}

/*
#define DIR_CLOSE FORWARD
#define DIR_OPEN BACKWARD

uint8_t direction = DIR_CLOSE;

void loop()
{
  if (direction == DIR_CLOSE) {
    Serial.println("Stänger");
    motor1->run(DIR_CLOSE);
  } else if (direction == DIR_OPEN) {
    Serial.println("Öppnar");
    motor1->run(DIR_OPEN);
  } else {
    Serial.println("Stop");
    motor1->run(RELEASE);
  }

  bool sw_open = digitalRead(PIN_VALVE_SW1) == 0;
  Serial.print(sw_open ? "Switch_Open True  " : "Switch_Open False ");

  bool sw_closed = digitalRead(PIN_VALVE_SW2) == 0;
  Serial.println(sw_closed ? "Switch_Closed True " : "Switch_Closed False");
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(400);

//  delay(700);

  if (i % 33 == 0)
  direction = BACKWARD;

  if (i++ % 8 == 0)
    direction = RELEASE;
  //    direction = (direction == FORWARD) ? BACKWARD : FORWARD;
}
*/