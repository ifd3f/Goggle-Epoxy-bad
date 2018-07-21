#include "input.hpp"

#include <algorithm>
#include <functional>
#include <memory>

using namespace epoxy::input;

Button::Button(int id): id(id) {

}

Encoder::Encoder(int id): id(id) {

}

ButtonQueueListener::ButtonQueueListener(Button* btn, std::queue<ButtonEvent>* queue): btn(btn), queue(queue) {

}

void ButtonQueueListener::update(int dt) {
    if (queue != nullptr) {
        bool state = btn->isPressed();
        if (last != state) {
            queue->emplace(ButtonEvent { btn, state });
            last = state;
        }
    }
}

void ButtonQueueListener::terminate() {
    delete this;
}

EncoderQueueListener::EncoderQueueListener(Encoder* enc, std::queue<EncoderEvent>* queue): enc(enc), queue(queue) {

}

void EncoderQueueListener::update(int dt) {
    if (queue != nullptr) {
        long ticks = enc->getTicks();
        if (last != ticks) {
            queue->emplace(EncoderEvent { enc, (signed char) (ticks - last) });
            last = ticks;
        }
    }
}

void EncoderQueueListener::terminate() {
    delete this;
}

void InputManager::addButton(Button* btn) {
    auto* ls = new ButtonQueueListener(btn, &bQueue);
    sched->addCommand(ls);
}

void InputManager::addEncoder(Encoder* enc) {
    auto* ls = new EncoderQueueListener(enc, &eQueue);
    sched->addCommand(ls);
}

InputManager::InputManager(Scheduler *sched): sched(sched) {

}

void InputManager::setInputListener(InputListener *listener) {
    this->listener = listener;
}

void InputManager::update(int dt) {
    while (!bQueue.empty()) {
        listener->onInput(bQueue.front());
        bQueue.pop();
    }
    while (!eQueue.empty()) {
        listener->onInput(eQueue.front());
        eQueue.pop();
    }
}

