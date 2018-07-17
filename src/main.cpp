#include <iostream>
#include <Eigen/Geometry>
#include <cairo.h>

int main(int argc, const char *argv[]) {
    auto srf = cairo_image_surface_create(CAIRO_FORMAT_A8, 128, 64);
    auto cr = cairo_create(srf);
    cairo_surface_destroy(srf);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_set_source_rgba(cr, 1, 1, 1, 1);
    cairo_rectangle(cr, 10, 10, 10, 10);
    cairo_fill(cr);
    cairo_image_surface_get_data(srf);
    std::cout << cairo_image_surface_get_stride(srf) << std::endl;
    cairo_surface_write_to_png(srf, "asdf.png");
    cairo_destroy(cr);
    return 0;
}
