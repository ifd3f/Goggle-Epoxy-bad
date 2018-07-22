//
// Created by Maxim on 7/21/2018.
//

#pragma once

#include <freetype/freetype.h>
#include <cairo>
#include <cairo.h>

namespace epoxy {
    class Assets {
    public:
        FT_Library ftLib;
        FT_Face scientifica;
        cairo_font_face_t* scientifica_cairo;

        Assets();
        ~Assets();
    };
}


