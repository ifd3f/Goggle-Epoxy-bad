#include <memory>

#include "devices/gpiobtn.hpp"
#include "devices/l3gd20.hpp"
#include "devices/lsm303.hpp"
#include "devices/mpl3115a2.hpp"
#include "devices/ssd1306.hpp"

#include "input.hpp"
#include "motion.hpp"
#include "weather.hpp"


using namespace epoxy;

namespace epoxy {

    const int ENCODER_ID = 0;
    const int BTN_H_ID = 0;
    const int BTN_X_ID = 1;
    const int BTN_Y_ID = 2;
    const int BTN_Z_ID = 3;

    class Hardware {
    public:
        // TODO: CHANGE THESE I2C ADDRS AND PIN #'s
        devices::SSD1306* screen;
        devices::LSM303DLHCAcc* acc;
        devices::L3GD20* gyro;
        devices::LSM303DLHCMag* mag;
        devices::GPIOQuadEncoder* encoder;
        devices::GPIOButton* btnH;
        devices::GPIOButton* btnX;
        devices::GPIOButton* btnY;
        devices::GPIOButton* btnZ;
        Hardware();
        ~Hardware();
    };
}