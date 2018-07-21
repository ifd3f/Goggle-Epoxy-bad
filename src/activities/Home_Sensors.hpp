#pragma once


#include <activity.hpp>

namespace epoxy {
    namespace activities {
        class Home_Sensors : public Activity, public input::InputListener {
            cairo_t* cr;
        public:
            void onStart() override;
            void onResume() override;
            void onUpdate(int dt) override;
            void onStop() override;
        };
    }
}
