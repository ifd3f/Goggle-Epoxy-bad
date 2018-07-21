//
// Created by Maxim on 7/20/2018.
//

#include "blank.hpp"
#include "Home_Sensors.hpp"

#include <memory>

using namespace epoxy::activities;

void Blank::onInput(epoxy::input::ButtonEvent ev) {
    ctx->activityManager->pushActivity(std::make_shared<auto>(new Home_Sensors()));
}

void Blank::onStart() {
    cr = cairo_create(ctx->hw.screen->getSurface());
}

void Blank::onResume() {
    ctx->input->setInputListener(this);
    cairo_set_source_rgba(cr, 0, 0, 0, 1);
    cairo_fill(cr);
}

void Blank::onStop() {
    delete cr;
}
