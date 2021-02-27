#include <Arduino.h>
#include "./quadSevenSegment.cpp"
#include "./webserver.hpp"
#include "./globals.hpp"

//TODO: all over shift registers

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

  web_setup();
}

void loop() {

  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(100);                        // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);

  web_loop();
}
