#include <cairo/cairo.h>
#include <wiringPiI2C.h>
#include "scheduler.hpp"


#define SSD1306_OUT_BUF_SIZE 1088  // 64 rows of 17. 0th bit is 0x40. 1-16th bits are data.
#define SSD1306_STRIDE 16

namespace epoxy {
    namespace devices {

        class SSD1306: public scheduler::Command {
            cairo_surface_t* surf;
            char addr;
            int fd;
            unsigned char drawBuf[SSD1306_OUT_BUF_SIZE] = {0};
            int sendCommand(unsigned char c);
        public:
            SSD1306(char addr);
            cairo_surface_t* getSurface();
            void initialize() override;
            void update(int dt) override;
            void writeDisplay();
        };

    }
}