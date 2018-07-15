#include "gpiobtn.hpp"

#include <wiringPi.h>

using namespace epoxy::devices;

GPIOButton::GPIOButton(int pin): pin(pin), invert(false) {

}

GPIOButton::GPIOButton(int pin, bool invert): pin(pin), invert(invert) {

}

void GPIOButton::initialize() {
    pinMode(pin, INPUT);
}

bool GPIOButton::isPressed() {
    return digitalRead(pin);
}

GPIOQuadEncoder::GPIOQuadEncoder(int pinA, int pinB): pinA(pinA), pinB(pinB) {

}

void GPIOQuadEncoder::initialize() {
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    lastState = 0;
}

void GPIOQuadEncoder::update(int dt) {
    bool a = digitalRead(pinA);
    bool b = digitalRead(pinB);
    unsigned char compare = (a << 4) | b;
    unsigned char ctr = QUAD_ENCODER_COUNTER;
    int pos;
    for (pos=0; pos < 4; pos++) {
        if ((~(QUAD_ENCODER_SEQ ^ compare) & ctr) == ctr) {
            break;
        }
        compare <<= 1;
        ctr <<= 1;
    }
    unsigned char lastPos = lastState & 0x03;
    if (lastPos == pos) {
        return; // do nothing
    } else if (lastPos == 4 && pos == 1) {
        ticks++;
        lastState = 0x11;
    } else if (lastPos == 1 && pos == 4) {
        ticks--;
        lastState = 0x04;
    } else {
        int d = pos - lastPos;
        if (d == 2 || d == -2) {
            ticks += ((lastState >> 4) & 1) ? 1 : -1;
            lastState = (lastState & 0x10) | pos;
        } else {
            ticks = ticks + d;
            lastState = (d > 0 ? 0x10 : 0) | pos;
        }
    }
}

long GPIOQuadEncoder::getTicks() {
    return ticks;
}

void GPIOQuadEncoder::reset() {
    ticks = 0;
}