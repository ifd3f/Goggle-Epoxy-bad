#include "ssd1306.hpp"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "exception.hpp"

using namespace epoxy::devices;

SSD1306::SSD1306(char addr): addr(addr) {
    surf = cairo_image_surface_create(CAIRO_FORMAT_A8, 128, 64);
}

void SSD1306::initialize() {
    if ((fd = open("/dev/i2c-0", O_RDWR)) < 0) {
        throw exception::I2CConnectionException(addr);
    }
    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        throw exception::I2CConnectionException(addr);
    }
}

void SSD1306::update(int dt) {
    writeDisplay();
}

void SSD1306::writeDisplay() {
    auto width = cairo_image_surface_get_width(surf);
    auto height = cairo_image_surface_get_height(surf);
    auto stride = cairo_image_surface_get_stride(surf);
    auto data = cairo_image_surface_get_data(surf);

    for (int y=0; y < height; y++) {
        auto row = data + y * stride;
        for (int x=0; x < width; x++) {
            char val = *(row + x);
            wiringPiI2CWriteReg8(fd, 0x40, val);
        }
    }
}