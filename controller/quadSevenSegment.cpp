#include <Arduino.h>

using namespace std;

class quadSevenSegment{
    private:

    int CLK;
    int IN;
    int PUSH;
    
    int *displays;         // display activate pins
    char displayBuffer[4]; // bits to display correct info on display
    char font[128];

    void pushToShiftReg(char data) {
        for (int i = 0; i < 8; i++) {
            // write input
            short bit = 1 << i;
            digitalWrite(IN, (data & bit) == bit);
            // latch clock
            digitalWrite(CLK, HIGH);
            digitalWrite(CLK, LOW);
        }
        digitalWrite(PUSH, HIGH);
        digitalWrite(PUSH, LOW);
        digitalWrite(IN, LOW);
    }

    public:

    int displayLightTime = 0;

    quadSevenSegment(int CLK, int IN, int PUSH, int displays[]) {
        //xxxx->pinMode(CLK,  OUTPUT);
        //xxxx->pinMode(IN,   OUTPUT);
        //xxxx->pinMode(PUSH, OUTPUT);
        // good pins: all on left side
        pinMode(15, OUTPUT);

        for (int i = 0; i < 4; i++) {
            //pinMode(displays[i], OUTPUT);
        }

        this->CLK = CLK;
        this->IN = IN;
        this->PUSH = PUSH;

        this->displays = displays;

        for (int i = 0; i < 128; i++) {
            font[i] = 0;
        }

        font['0'] = 0b01111110;
        font['1'] = 0b01001000;
        font['2'] = 0b00111101;
        font['3'] = 0b01101101;
        font['4'] = 0b01001011;
        font['5'] = 0b01100111;
        font['6'] = 0b01110111;
        font['7'] = 0b01001100;
        font['8'] = 0b01111111;
        font['9'] = 0b01101111;
        font['A'] = 0b01011111;
        font['B'] = 0b01110011;
        font['C'] = 0b00110001;
        font['D'] = 0b01111001;
        font['E'] = 0b00110111;
        font['F'] = 0b00010111;
        font[ 0 ] = 0b00000001;
        font[ 1 ] = 0b01000000;
        font[ 2 ] = 0b00100000;
        font[ 3 ] = 0b00010000;

        //  3
        // 2 4
        //  1
        // 5 7
        //  68
    }

    void setDot(short i, bool active) {
        this->displayBuffer[i] = this->displayBuffer[i] & 0b01111111 | 0b10000000 * active;
    }

    void setDisplay(char data[]) {
        for (int i = 0; i < 4; i++) {
            this->displayBuffer[i] = data[i] & 0b01111111;
        }
    }

    void updateDisplay() {
        for (int i = 0; i < 4; i++) {
            pushToShiftReg(this->displayBuffer[i]);
            digitalWrite(this->displays[i],HIGH);
            delay(this->displayLightTime);
            digitalWrite(this->displays[i],LOW);
        }
    }
};