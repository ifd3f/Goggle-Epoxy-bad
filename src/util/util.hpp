#pragma once

#include <wiringPiI2C.h>
#include <chrono>

namespace epoxy {
    namespace util {
        void readBlockData(int fd, int reg, int bytes, char buf[]);
        long long getMillis();
    }
}