#include <wiringPiI2C.h>

namespace epoxy {
    namespace util {
        void readBlockData(int fd, int reg, const int bytes, char buf[]);
    }
}