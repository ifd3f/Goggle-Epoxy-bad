#pragma once

#include "activity.hpp"
#include "input.hpp"

namespace epoxy {
    namespace activities {
        class Blank : public Activity, public input::InputListener {
            cairo_t* cr;
        public:
            void onInput(input::ButtonEvent ev) override;
            void onStart() override;
            void onResume() override;
            void onStop() override;
        };
    }
}
