#include "mpl3115a2.hpp"

#include <wiringPiI2C.h>
#include "util/util.hpp"

using namespace epoxy::util;
using namespace epoxy::devices;

double MPL3115A2::getAltitude() {
    if (!(status & 1)) {
        updateAltThm();
    }
    return alt;
}

double MPL3115A2::getPressure() {
    if (!(status & 2)) {
        updateBar();
    }
    return bar;
}

double MPL3115A2::getTemperature() {
    if (!(status & 1)) {
        updateAltThm();
    }
    return alt;
}

MPL3115A2::MPL3115A2(char addr): addr(addr) {
}

void MPL3115A2::initialize() {
    fd = wiringPiI2CSetup(addr);
}

void MPL3115A2::update(int dt) {
    status = 0;
}

void MPL3115A2::updateAltThm() {
    wiringPiI2CWriteReg8(fd, 0x26, 0xB9);
    char buf[6];
    readBlockData(fd, 0x00, 6, buf);
    int rawAltitude = ((int)buf[1] << 16) | ((int)buf[2] << 8) | ((int)buf[3] & 0xF0);
    int rawTemp = ((int)buf[4] << 8) | ((int)buf[5] & 0xF0);
    alt = rawAltitude / 256.0;
    thm = rawTemp / 256.0;
    status &= 1;
}

void MPL3115A2::updateBar() {
    wiringPiI2CWriteReg8(fd, 0x26, 0x39);
    char buf[4];
    readBlockData(fd, 0x00, 4, buf);
    int rawPres = ((int)buf[1] << 16) | ((int)buf[2] << 8) | ((int)buf[3] & 0xF0);
    bar = rawPres / 64.0;
    status &= 2;
}
