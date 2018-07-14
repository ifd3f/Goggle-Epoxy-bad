#pragma once

#include "motion.hpp"
#include "scheduler.hpp"
#include "weather.hpp"

using namespace epoxy;
namespace epoxy {
    namespace devices {

        class MPL3115A2 : public scheduler::Command, public weather::Altimeter, public weather::Barometer, public weather::Thermometer {
            char addr;
            int fd;
            /**
             * tracks if values have been updated this loop.
             * Bit 8: alt, thm
             * Bit 7: bar
             */
            char status;
            double alt, bar, thm;
            void updateAltThm();
            void updateBar();
        public:
            MPL3115A2(char addr);
            void initialize() override;
            void update(int dt) override;

            double getAltitude() override;
            double getPressure() override;
            double getTemperature() override;

            friend class MPL3115A2Altimeter;
            friend class MPL3115A2Barometer;
            friend class MPL3115A2Thermometer;
        };
    }
}