//
// Created by Maxim on 7/20/2018.
//

#include "Home_Sensors.hpp"

void activities::Home_Sensors::onResume() {
    ctx->input->setInputListener(this);
}

void activities::Home_Sensors::onStart() {
    cr = ctx->hw.screen->createContext();
}

void activities::Home_Sensors::onStop() {
    delete cr;
}

void activities::Home_Sensors::onUpdate(int dt) {
    auto ori = ctx->orientation->getOrientation();
    double temp = ctx->hw.thm->getTemperature();
    auto rotMatrix = ori.toRotationMatrix();
}
