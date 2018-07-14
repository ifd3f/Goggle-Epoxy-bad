#pragma once

#include "motion.hpp"
#include "scheduler.hpp"
#include "weather.hpp"

using namespace epoxy;
namespace epoxy {
    namespace devices {

        class MPL3115A2;

        class MPL3115A2Altimeter : public weather::Altimeter {
            char addr;
            MPL3115A2* parent;
        public:
            double getAltitude() override;
            friend class MPL3115A2;
        };

        class MPL3115A2Barometer : public weather::Barometer {
            char addr;
            MPL3115A2* parent;
        public:
            double getPressure() override;
            friend class MPL3115A2;
        };

        class MPL3115A2Thermometer : public weather::Thermometer {
            char addr;
            MPL3115A2* parent;
        public:
            double getTemperature() override;
            friend class MPL3115A2;
        };

        class MPL3115A2 : public scheduler::Command {
            MPL3115A2Altimeter altimeter;
            MPL3115A2Barometer barometer;
            MPL3115A2Thermometer thermometer;
            char addr;
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

            weather::Barometer* getBarometer();
            weather::Altimeter* getAltimeter();
            weather::Thermometer* getThermometer();

            friend class MPL3115A2Altimeter;
            friend class MPL3115A2Barometer;
            friend class MPL3115A2Thermometer;
        };
    }
}