#include <iostream>
#include <Eigen/Geometry>
#include <cairo/cairo.h>


int main(int argc, const char *argv[]) {
    auto surf = cairo_image_surface_create(CAIRO_FORMAT_A8, 128, 64);
    auto cr = cairo_create(surf);
    cairo_surface_destroy(surf);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_set_source_rgba(cr, 1, 1, 1, 1);
    cairo_rectangle(cr, 10, 10, 10, 10);
    cairo_fill(cr);
    
    unsigned char *data = cairo_image_surface_get_data(surf);
    int width = cairo_image_surface_get_width(surf);
    int height = cairo_image_surface_get_height(surf);
    int stride = cairo_image_surface_get_stride(surf);
    for (int i = 0; i < height; i++) {
        unsigned char *row = data + i * stride;
        for (int j = 0; j < width; j++) {
            char val = *(row + j);
            if (val & 0x30) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }

    cairo_surface_write_to_png(surf, "asdf.png");
    cairo_destroy(cr);
    return 0;
}
