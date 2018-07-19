#pragma once

namespace epoxy {
    namespace weather {

        class Barometer {
        public:
            virtual ~Barometer() {};
            virtual double getPressure() = 0;
        };

        class Altimeter {
        public:
            virtual ~Altimeter() {};
            virtual double getAltitude() = 0;
        };

        class Thermometer {
        public:
            virtual ~Thermometer() {};
            virtual double getTemperature() = 0;
        };

    }
}