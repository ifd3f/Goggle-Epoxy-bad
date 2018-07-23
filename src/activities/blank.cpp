#include "blank.hpp"
#include "Home_Sensors.hpp"

#include <memory>

using namespace epoxy::activities;

void Blank::onInput(epoxy::input::ButtonEvent ev) {
    auto* next = new Home_Sensors;
    ctx->activityManager->pushActivity(std::shared_ptr<Activity>(static_cast<Activity*>(next)));
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
}
