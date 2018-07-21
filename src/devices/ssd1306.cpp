#include "ssd1306.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "exception.hpp"

using namespace epoxy::devices;

SSD1306::SSD1306(char addr): addr(addr) {
    surf = cairo_image_surface_create(CAIRO_FORMAT_A8, PIXEL_WIDTH, PIXEL_HEIGHT);
    for (int i=0; i < OUT_BUF_SIZE; i += OUT_BUF_STRIDE) {
        drawBuf[i] = 0x40;
    }
}

int SSD1306::sendCommand(unsigned char c) {
    unsigned char buf[] = {0x00, c};
    return write(fd, buf, 2);
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
    auto stride = cairo_image_surface_get_stride(surf);
    auto data = cairo_image_surface_get_data(surf);

    for (int y=0; y < 64; y++) {
        auto base_bi = drawBuf + OUT_BUF_STRIDE * y;
        int base_sx = stride * y;
        for (int bx=1; bx < OUT_BUF_STRIDE; bx++) {
            int base_si = base_sx + 8 * bx;
            char byteBuf = 0;
            for (int bj=0; bj < 8; bj++) {
                auto si = data + base_si + bj;
                auto val = (*si) & 0x80;
                byteBuf |= val >> bj;
            }
            *(base_bi + bx) = byteBuf;
        }
    }

    char columnAddr[] = {0x21, 0, 127};
    write(fd, columnAddr, 3);
    char pageAddr[] = {0x22, 0, 7};
    write(fd, pageAddr, 3);

    for (int i=0; i < OUT_BUF_SIZE; i += OUT_BUF_STRIDE) {        
        write(fd, drawBuf + i, 16);
    }
}

cairo_surface_t* SSD1306::getSurface() {
    return surf;
}

cairo_t *SSD1306::createContext() {
    return cairo_create(getSurface());
}
