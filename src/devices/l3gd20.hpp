#pragma once

#include <wiringPiI2C.h>
#include "motion.hpp"

#define L3GD20_250 0x00
#define L3GD20_500 0x10
#define L3GD20_2000 0x20


using namespace epoxy;

namespace epoxy {
    namespace devices {
        class L3GD20 : public motion::Gyro, public scheduler::Command {
            int fd;
            char addr, scaleByte;
            double scaleValue;
            double x, y, z;
        public:
            L3GD20(char addr, char scale);
            void initialize() override;
            void update(int dt) override;
            double getX() override;
            double getY() override;
            double getZ() override;
        };
    }
}
