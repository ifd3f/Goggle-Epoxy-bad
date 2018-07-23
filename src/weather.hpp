#pragma once

namespace epoxy {
    namespace weather {

        class Barometer {
        public:
            virtual ~Barometer() = default;
            virtual double getPressure() = 0;
        };

        class Altimeter {
        public:
            virtual ~Altimeter() = default;
            virtual double getAltitude() = 0;
        };

        class Thermometer {
        public:
            virtual ~Thermometer() = default;
            virtual double getTemperature() = 0;
        };

    }
}