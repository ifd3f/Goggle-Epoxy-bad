#pragma once


#include <activity.hpp>
#include <Eigen>


namespace epoxy {
    namespace activities {
        class Home_Sensors : public Activity, public input::InputListener {
            cairo_t* cr;
            static const int LONG_INC = 15;
            static const int LONG_COUNT = 24;
            static const double LONG_LEN = 0.1;

            static const int LAT_INC = 15;
            static const int LAT_COUNT = 24;
            static const double LAT_LEN = 0.1;

            static_assert(LONG_INC * LONG_COUNT == 360, "Latitude inc * count must equal 360.");
            static_assert(LAT_INC * LAT_COUNT == 360, "Longitude inc * count must equal 360.");

            static bool matrixInitialized = false;
            static Eigen::Matrix<double, LAT_COUNT * 2, 4> MAT_LAT;
            static Eigen::Matrix<double, LONG_COUNT * 2, 4> MAT_LONG;

            static void lazyInitMatrices();
        public:
            Home_Sensors();
            void onStart() override;
            void onResume() override;
            void onUpdate(int dt) override;
            void onStop() override;
        };
    }
}
