#define DEBUG true

#include <Arduino.h>

using namespace std;

class quadSevenSegment{
    private:

    int CLK;
    int IN;
    int PUSH;
    
    char displayBuffer[5]; // bits to display correct info on display
    char font[128];

    bool active = true;

    void pushToShiftReg(char data, short id) {

        // ADDR: 0123456789ABCDEF
        // DATA: |-DATA-|    |ID|
        // data will contain the signal for a single display
        // id will select the display
        
        // id part
        for (int i = 0; i < 8; i++) {
            digitalWrite(IN, id == i);
            #if DEBUG
                Serial.print((int)(id == i));
            #endif
            digitalWrite(CLK, HIGH);
            digitalWrite(CLK, LOW);
        }

        // data part
        for (int i = 0; i < 8; i++) {
            short bit = 1 << i;
            digitalWrite(IN, (data & bit) == bit);
            #if DEBUG
                Serial.print((int)((data & bit) == bit));
            #endif
            digitalWrite(CLK, HIGH);
            digitalWrite(CLK, LOW);
        }
        
        #if DEBUG
            Serial.print("\n");
        #endif
        digitalWrite(PUSH, HIGH);
        digitalWrite(PUSH, LOW);
        digitalWrite(IN, LOW);
    }

    public:

    int displayLightTime = 0;

    quadSevenSegment(int CLK, int IN, int PUSH) {
        pinMode(CLK,  OUTPUT);
        pinMode(IN,   OUTPUT);
        pinMode(PUSH, OUTPUT);

        for (int i = 0; i < 4; i++) {
            //pinMode(displays[i], OUTPUT);
        }

        this->CLK = CLK;
        this->IN = IN;
        this->PUSH = PUSH;

        for (int i = 0; i < 128; i++) {
            font[i] = 0;
        }
        
        this->displayBuffer[4] = 0;

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

        font[ 0 ] = 0b00000000;

        font[ 1 ] = 0b00000001;
        font[ 2 ] = 0b01000000;
        font[ 3 ] = 0b00100000;
        font[ 4 ] = 0b00010000;

        //  3
        // 2 4
        //  1
        // 5 7
        //  68
    }

    void activate() {
        this->active = true;
    }

    void deactivate() {
        this->active = false;
    }

    void setDot(short i, bool active) {
        this->displayBuffer[i] = this->displayBuffer[i] & 0b01111111 | 0b10000000 * active;
    }

    void setDisplay(char data[]) {
        for (int i = 0; i < 4; i++) {
            this->displayBuffer[i] = font[data[i]] & 0b01111111;
        }
    }

    void allOn() {
        char data[] = {'8','8','8','8'};
        setDisplay(data);
        for (int i = 0; i < 4; i++) setDot(i, true);
    }

    void clear() {
        char data[] = {0,0,0,0};
        setDisplay(data);
        for (int i = 0; i < 4; i++) setDot(i, false);
    }

    void updateDisplay() {
        if (!active) { // disable shift out register
            return;
        }
        int x;
        for (short i = 0; i < 5; i++) {
            x = i;
            if (i == 4) x = 8;
            pushToShiftReg(this->displayBuffer[i],x);
            delay(this->displayLightTime);
        }
        #if DEBUG
            Serial.print("\n");
        #endif
    }
};