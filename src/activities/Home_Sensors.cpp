#include "Home_Sensors.hpp"

#include <cmath>
#include <freetype2/ft2build.h>
#include <pango/pangocairo.h>

void activities::Home_Sensors::onResume() {
    ctx->input->setInputListener(this);
}

void activities::Home_Sensors::onStart() {
    cr = ctx->hw.screen->createContext();
    pr = pango_cairo_create_context(cr);
}

void activities::Home_Sensors::onStop() {
}

void activities::Home_Sensors::onUpdate(int dt) {
    auto ori = ctx->orientation->getOrientation();
    double temp = ctx->hw.thm->getTemperature();

    auto proj = Eigen::Affine3d::Identity();
    proj.rotate(ori);

    auto matLat = proj * MAT_LAT;
    auto matLong = proj * MAT_LONG;

    cairo_set_source_rgba(cr, 0, 0, 0, 0);
    cairo_fill(cr);

    cairo_set_source_rgba(cr, 1, 1, 1, 1);
    cairo_set_line_width(cr, 1);

    for (int i=0; i < LAT_COUNT * 2; i += 2) {
        if (matLat(3, i) < 0) {
            continue;
        }
        cairo_move_to(cr, matLat(0, i), matLat(1, i));
        cairo_line_to(cr, matLat(0, i + 1), matLat(1, i + 1));
        cairo_stroke(cr);
    }
    for (int i=0; i < LONG_COUNT * 2; i += 2) {
        if (matLong(3, i) < 0) {
            continue;
        }
        cairo_move_to(cr, matLong(0, i), matLong(1, i));
        cairo_line_to(cr, matLong(0, i + 1), matLong(1, i + 1));
        cairo_stroke(cr);
    }

    PangoLayout* layout;
    pango_layout_set_font_description(layout, ctx->res.scientifica);

}

activities::Home_Sensors::Home_Sensors() {
    lazyInitMatrices();
}

void activities::Home_Sensors::lazyInitMatrices() {
    if (!matrixInitialized) {
        matrixInitialized = true;
        for (int i=0; i < LAT_COUNT; i++) {
            int j1 = 2*i;
            int j2 = j1 + 1;
            double a = double(i * LAT_INC) * M_PI / 180;
            double x = std::cos(a);
            double y = std::sin(a);
            MAT_LAT(0, j1) = x;
            MAT_LAT(1, j1) = y;
            MAT_LAT(2, j1) = LAT_LEN;
            MAT_LAT(3, j1) = 1;

            MAT_LAT(0, j2) = x;
            MAT_LAT(1, j2) = y;
            MAT_LAT(2, j2) = -LAT_LEN;
            MAT_LAT(3, j2) = 1;
        }

        for (int i=0; i < LONG_COUNT; i++) {
            int j1 = 2*i;
            int j2 = j1 + 1;
            double a = double(i * LONG_INC) * M_PI / 180;
            double x = std::cos(a);
            double z = std::sin(a);
            MAT_LONG(0, j1) = x;
            MAT_LONG(1, j1) = LONG_LEN;
            MAT_LONG(2, j1) = z;
            MAT_LONG(3, j1) = 1;

            MAT_LONG(0, j2) = x;
            MAT_LONG(1, j2) = -LONG_LEN;
            MAT_LONG(2, j2) = z;
            MAT_LONG(3, j2) = 1;
        }
    }
}
