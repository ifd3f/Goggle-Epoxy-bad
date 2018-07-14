#include "lsm303.hpp"

using namespace epoxy;
using namespace epoxy::devices;


LSM303DLHCAcc::LSM303DLHCAcc(char addr, char scaleByte): addr(addr), scaleByte(scaleByte) {
    switch (scaleByte) {
        case LSM303_ACC_2G:
            scaleValue = 2;
        break;
        case LSM303_ACC_4G:
            scaleValue = 4;
        break;
        case LSM303_ACC_8G:
            scaleValue = 8;
        break;
    }
    scaleValue /= 32768;
}

void LSM303DLHCAcc::initialize() {
    fd = wiringPiI2CSetup(addr);
    wiringPiI2CWriteReg8(fd, 0x20, 0x27);
    wiringPiI2CWriteReg8(fd, 0x23, scaleByte & 0x30);
}

void LSM303DLHCAcc::update(int dt) {
    char buf[6];
    for (int i=0,r=0x28; r <= 0x2D; i++,r++) {
        buf[i] = wiringPiI2CReadReg8(fd, r);
    }
    int rx, ry, rz;
    rx = (int)buf[0] << 8 | buf[1];
    ry = (int)buf[2] << 8 | buf[3];
    rz = (int)buf[4] << 8 | buf[5];

    x = rx * scaleValue;
    y = rx * scaleValue;
    z = rx * scaleValue;
}

double LSM303DLHCAcc::getX() {
    return x;
}

double LSM303DLHCAcc::getY() {
    return y;
}

double LSM303DLHCAcc::getZ() {
    return z;
}

LSM303DLHCMag::LSM303DLHCMag(char addr, char scaleByte): addr(addr), scaleByte(scaleByte) {
    switch (scaleByte) {
        case LSM303_MAG_13:
            scaleValue = 1.3;
        break;
        case LSM303_MAG_25:
            scaleValue = 2.5;
        break;
        case LSM303_MAG_40:
            scaleValue = 4.0;
        break;
        case LSM303_MAG_81:
            scaleValue = 8.1;
        break;
    }
    scaleValue /= 2048;
}

void LSM303DLHCMag::initialize() {
    fd = wiringPiI2CSetup(addr);
    wiringPiI2CWriteReg8(fd, 0x20, 0x27);
    wiringPiI2CWriteReg8(fd, 0x23, scaleByte & 0x30);
}

void LSM303DLHCMag::update(int dt) {
    char buf[6];
    for (int i=0,r=0x03; r <= 0x08; i++,r++) {
        buf[i] = wiringPiI2CReadReg8(fd, r);
    }
    int rx, ry, rz;
    rx = (int)buf[0] << 8 | buf[1];
    rz = (int)buf[2] << 8 | buf[3];
    ry = (int)buf[4] << 8 | buf[5];

    x = rx * scaleValue;
    y = rx * scaleValue;
    z = rx * scaleValue;
}

double LSM303DLHCMag::getX() {
    return x;
}

double LSM303DLHCMag::getY() {
    return y;
}

double LSM303DLHCMag::getZ() {
    return z;
}

