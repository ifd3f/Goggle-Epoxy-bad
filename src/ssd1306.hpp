#include <cairo/cairo.h>
#include <wiringPiI2C.h>
#include "scheduler.hpp"

namespace epoxy {
    namespace devices {

        class SSD1306: public scheduler::Command {
            cairo_surface_t* surf;
            char addr;
            int fd;
        public:
            SSD1306(char addr);
            void initialize() override;
            void update(int dt) override;
            void writeDisplay();
        };

    }
}