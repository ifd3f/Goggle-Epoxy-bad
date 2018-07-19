#include "l3gd20.hpp"

#include <cmath>
#include <wiringPiI2C.h>

using namespace epoxy::devices;

L3GD20::L3GD20(char addr, char scale):
        addr(addr), 
        scaleByte(scale) {
    switch (scale) {
        case L3GD20_250:
            scaleValue = 250;
        break;
        case L3GD20_500:
            scaleValue = 500;
        break;
        case L3GD20_2000:
            scaleValue = 2000;
        break;
    }

    scaleValue *= M_PI / 180 / 32768;
}

void L3GD20::initialize() {
    fd = wiringPiI2CSetup(addr);
    wiringPiI2CWriteReg8(fd, 0x20, 0x0F);
}

void L3GD20::update(int dt) {
    char buf[6];
    for (int i=0,r=0x28; r <= 0x2D; i++,r++) {
        buf[i] = wiringPiI2CReadReg8(fd, r);
    }
    int rx, ry, rz;
    rx = (int)buf[0] << 8 | buf[1];
    ry = (int)buf[2] << 8 | buf[3];
    rz = (int)buf[4] << 8 | buf[5];

    x = rx * scaleValue;
    y = ry * scaleValue;
    z = rz * scaleValue;
}

double L3GD20::getX() {
    return x;
}

double L3GD20::getY() {
    return y;
}

double L3GD20::getZ() {
    return z;
}
