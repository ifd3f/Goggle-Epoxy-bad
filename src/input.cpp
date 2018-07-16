#include "input.hpp"

#include <algorithm>
#include <functional>
#include <memory>

using namespace epoxy::input;

Button::Button(int id): id(id) {

}

Encoder::Encoder(int id): id(id) {

}

ButtonListener::ButtonListener(std::shared_ptr<Button> btn): btn(btn) {

}

void ButtonListener::update(int dt) {
    if (queue != nullptr) {
        bool state = btn->isPressed();
        if (last != state) {
            queue->emplace(ButtonEvent { btn.get(), state });
            last = state;
        }
    }
}

void ButtonListener::attachEventQueue(std::shared_ptr<std::queue<ButtonEvent>> queue) {
    this->queue = queue;
}

EncoderListener::EncoderListener(std::shared_ptr<Encoder> enc): enc(enc) {

}

void EncoderListener::update(int dt) {
    if (queue != nullptr) {
        long ticks = enc->getTicks();
        if (last != ticks) {
            queue->emplace(EncoderEvent { enc.get(), (signed char) (ticks - last) });
            last = ticks;
        }
    }
}

void EncoderListener::attachEventQueue(std::shared_ptr<std::queue<EncoderEvent>> queue) {
    this->queue = queue;
}
