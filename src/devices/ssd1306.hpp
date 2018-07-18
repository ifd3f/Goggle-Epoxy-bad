#pragma once

#include <cairo/cairo.h>
#include <wiringPiI2C.h>
#include "scheduler.hpp"


namespace epoxy {
    namespace devices {

        class SSD1306: public scheduler::Command {
            static const int PIXEL_WIDTH = 128;
            static const int PIXEL_HEIGHT = 64;
            static const int OUT_BUF_SIZE = (PIXEL_WIDTH / 8 + 1) * PIXEL_HEIGHT;
            static const int OUT_BUF_STRIDE = 17;

            cairo_surface_t* surf;
            char addr;
            int fd;
            unsigned char drawBuf[OUT_BUF_SIZE] = {0};
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