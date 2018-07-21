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
