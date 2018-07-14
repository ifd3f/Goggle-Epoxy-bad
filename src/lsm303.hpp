#include <wiringPiI2C.h>

#include "motion.hpp"
#include "scheduler.hpp"

#define LSM303_ACC_2G 0x10
#define LSM303_ACC_4G 0x20
#define LSM303_ACC_8G 0x30

// note: doesn't include all gain values
#define LSM303_MAG_13 0x20
#define LSM303_MAG_25 0x60
#define LSM303_MAG_40 0x80
#define LSM303_MAG_81 0xD0


using namespace epoxy;

namespace epoxy {
    namespace devices {

        class LSM303DLHCAcc : public scheduler::Command, public motion::VectorOutput {
            char addr, scaleByte;
            int fd;
            double scaleValue;
            double x, y, z;
        public:
            LSM303DLHCAcc(char addr, char scaleByte);
            void initialize() override;
            void update(int dt) override;
            double getX() override;
            double getY() override;
            double getZ() override;
        };

        class LSM303DLHCMag : public scheduler::Command, public motion::VectorOutput {
            char addr, scaleByte;
            int fd;
            double scaleValue;
            double x, y, z;
        public:
            LSM303DLHCMag(char addr, char scaleByte);
            void initialize() override;
            void update(int dt) override;
            double getX() override;
            double getY() override;
            double getZ() override;
        };
        
    }
}
