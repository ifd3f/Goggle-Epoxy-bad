#include <iostream>
extern "C" {
#include <cairo.h>
}
#include "devices/ssd1306.hpp"


using namespace epoxy;

int main(int argc, const char *argv[]) {
    devices::SSD1306 disp(0x3C); // if not, try 0x7A

    disp.initialize();

    auto* cr = cairo_create(disp.getSurface());

    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle(cr, 10, 10, 64, 30);

    disp.writeDisplay();
    return 0;
}
