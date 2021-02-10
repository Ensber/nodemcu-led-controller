#include <Arduino.h>
#include "./quadSevenSegment.cpp"
//#include "./webserver.cpp"

//TODO: all over shift registers

// shift register pins
#define SR_CLK 2
#define SR_IN 4
#define SR_PUSH 5

// PWM Pins
#define PWM_R 15
#define PWM_G 12
#define PWM_B 14

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("\n\nStarting...");

  quadSevenSegment QSS = quadSevenSegment(
    SR_CLK, 
    SR_IN, 
    SR_PUSH
  );

  char display[] = {'1','2','3','4'};
  QSS.setDisplay(display);
  QSS.updateDisplay();
  QSS.allOn();
  QSS.updateDisplay();
  // QSS.deactivate();
  QSS.clear();
  QSS.updateDisplay();
  // QSS.activate();
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                        // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
}
