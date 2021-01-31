#include <Arduino.h>
#include "quadSevenSegment.cpp"

// GPIO pin declaration
#define SR_CLK 6
#define SR_IN 7
#define SR_PUSH 11

#define DIS1 8
#define DIS2 9
#define DIS3 10
#define DIS4 13

// PWM Pins
#define PWM_R 15
#define PWM_G 12
#define PWM_B 14

void setup() {
    //pinMode(1, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    int displays[4] = {DIS1, DIS2, DIS3, DIS4};
    quadSevenSegment QSS = quadSevenSegment(
        SR_CLK, SR_IN, SR_PUSH, 
        displays
    );
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);   
}