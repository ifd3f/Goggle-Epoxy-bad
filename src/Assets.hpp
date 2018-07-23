//
// Created by Maxim on 7/21/2018.
//

#pragma once

extern "C" {
#include <pango/pangocairo.h>
#include <pango/pango-font.h>
}

namespace epoxy {
    class Assets {
    public:
        PangoFontDescription* scientifica;

        Assets();
        ~Assets();
    };
}


