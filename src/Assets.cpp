//
// Created by Maxim on 7/21/2018.
//

#include <cairo-ft.h>
#include "Assets.hpp"


epoxy::Assets::Assets() {
    if (FT_Init_FreeType(&ftLib)) {
        throw "Could not init freetype";
    }
    if (FT_New_Face(ftLib, "scientifica-11.bdf", 0, &scientifica)) {
        throw "Could not load scientifica-11.bdf";
    }
    scientifica_cairo = cairo_ft_font_face_create_for_ft_face(scientifica, 0);
}

epoxy::Assets::~Assets() {
    delete scientifica;
    delete scientifica_cairo;
}
