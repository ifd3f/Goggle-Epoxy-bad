#include "mpl3115a2.hpp"

#include <wiringPiI2C.h>
#include "util.hpp"

using namespace epoxy::util;
using namespace epoxy::devices;

double MPL3115A2Altimeter::getAltitude() {
    if (!(parent->status & 1)) {
        parent->updateAltThm();
    }
    return parent->alt;
}

double MPL3115A2Barometer::getPressure() {
    if (!(parent->status & 2)) {
        parent->updateBar();
    }
    return parent->bar;
}

double MPL3115A2Thermometer::getTemperature() {
    if (!(parent->status & 1)) {
        parent->updateAltThm();
    }
    return parent->alt;
}

MPL3115A2::MPL3115A2(char addr): addr(addr) {
    altimeter.parent = this;
    barometer.parent = this;
    thermometer.parent = this;

    barometer.addr = addr;
    altimeter.addr = addr;
    thermometer.addr = addr;
}

void MPL3115A2::initialize() {
    wiringPiI2CSetup(addr);
}

void MPL3115A2::update(int dt) {
    status = 0;
}

void MPL3115A2::updateAltThm() {
    wiringPiI2CWriteReg8(addr, 0x26, 0xB9);
    char buf[6];
    readBlockData(addr, 0x00, 6, buf);
    int rawAltitude = ((int)buf[1] << 16) | ((int)buf[2] << 8) | ((int)buf[3] & 0xF0);
    int rawTemp = ((int)buf[4] << 8) | ((int)buf[5] & 0xF0);
    alt = rawAltitude / 256.0;
    thm = rawTemp / 256.0;
    status &= 1;
}

void MPL3115A2::updateBar() {
    wiringPiI2CWriteReg8(addr, 0x26, 0x39);
    char buf[4];
    readBlockData(addr, 0x00, 4, buf);
    int rawPres = ((int)buf[1] << 16) | ((int)buf[2] << 8) | ((int)buf[3] & 0xF0);
    bar = rawPres / 64.0;
    status &= 2;
}

weather::Altimeter* MPL3115A2::getAltimeter() {
    return &altimeter;
}

weather::Barometer* MPL3115A2::getBarometer() {
    return &barometer;
}

weather::Thermometer* MPL3115A2::getThermometer() {
    return &thermometer;
}

