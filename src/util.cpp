#include "util.hpp"

#include <wiringPiI2C.h>

void epoxy::util::readBlockData(int fd, int reg, int bytes, char buf[]) {
    for (int i=0; i < bytes; i++) {
        buf[i] = wiringPiI2CReadReg8(fd, reg);
    }
}

long long epoxy::util::getMillis() {
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}
