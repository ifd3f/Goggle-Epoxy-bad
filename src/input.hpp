#pragma once

#include <functional>

#include "scheduler.hpp"

using namespace epoxy::scheduler;
namespace epoxy {
    namespace input {
        
        class Button : public Command {
            std::function<void(Button*)> onPressedListener, onReleasedListener;
        public:
            void setOnPressedListener(std::function<void(Button*)> listener);
            void setOnReleasedListener(std::function<void(Button*)> listener);
            virtual bool isPressed() = 0;
        };

        class Encoder : public Command {
            std::function<void(Encoder*, int)> onChangedListener;
        public:
            virtual void reset() = 0;
            virtual long getTicks() = 0;
            void setOnChangedListener(std::function<void(Encoder*, int)> listener);
        };

    }
}