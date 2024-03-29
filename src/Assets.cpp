extern "C" {
#include <cairo-ft.h>
#include <pango/pangocairo.h>
#include <pango/pango-font.h>
}

#include "Assets.hpp"


epoxy::Assets::Assets() {
    scientifica = pango_font_description_from_string("scientifica");
}

epoxy::Assets::~Assets() {
    pango_font_description_free(scientifica);
}
