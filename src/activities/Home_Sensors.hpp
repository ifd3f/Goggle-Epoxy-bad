#pragma once


extern "C" {
#include <pango/pangocairo.h>
}

#include <activity.hpp>
#include <Eigen/Core>


namespace epoxy {
    namespace activities {
        class Home_Sensors : public Activity, public input::InputListener {
            static const int LONG_INC = 15;
            static const int LONG_COUNT = 24;
            static constexpr double LONG_LEN = 0.1;

            static const int LAT_INC = 15;
            static const int LAT_COUNT = 24;
            static constexpr double LAT_LEN = 0.1;

            static_assert(LONG_INC * LONG_COUNT == 360, "Latitude inc * count must equal 360.");
            static_assert(LAT_INC * LAT_COUNT == 360, "Longitude inc * count must equal 360.");

            Eigen::Matrix<double, 4, LAT_COUNT * 2> MAT_LAT;
            Eigen::Matrix<double, 4, LONG_COUNT * 2> MAT_LONG;

            cairo_t* cr;
            PangoContext *pr;

        public:
            Home_Sensors();

            void onStart() override;
            void onResume() override;
            void onUpdate(int dt) override;
            void onStop() override;
        };
    }
}
