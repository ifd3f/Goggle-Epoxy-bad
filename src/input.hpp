#pragma once

#include <functional>

#include "scheduler.hpp"

using namespace epoxy::scheduler;
namespace epoxy {
    namespace input {
        
        class Button : public Command {
            bool lastPressed = false;
        public:
            virtual bool isPressed() = 0;
        };

        class Encoder : public Command {
        public:
            virtual void reset() = 0;
            virtual long getTicks() = 0;
        };

    }
}