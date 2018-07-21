#pragma once

#include "activity.hpp"
#include "input.hpp"

namespace epoxy {
    namespace activities {
        class Blank : public Activity, public input::InputListener {
        public:
            void onInput(input::ButtonEvent ev) override;
        };
    }
}
