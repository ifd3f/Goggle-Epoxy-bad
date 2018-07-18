#pragma once

#include <wiringPiI2C.h>
#include "motion.hpp"

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
