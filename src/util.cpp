#include "util.hpp"

#include <wiringPiI2C.h>

using namespace epoxy::util;

void readBlockData(int fd, int reg, const int bytes, char buf[]) {
    for (int i=0; i < bytes; i++) {
        buf[i] = wiringPiI2CReadReg8(fd, reg);
    }
}