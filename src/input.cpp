#include "input.hpp"


using namespace epoxy::input;

void Button::setOnPressedListener(std::function<void(Button*)> listener) {
    this->onPressedListener = listener;
}

void Button::setOnReleasedListener(std::function<void(Button*)> listener) {
    this->onReleasedListener = listener;
}

void Encoder::setOnChangedListener(std::function<void(Encoder*, int)> listener) {
    this->onChangedListener = listener;
}
