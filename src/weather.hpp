namespace epoxy {
    namespace weather {

        class Barometer {
        public:
            virtual double getPressure() = 0;
        };

        class Altimeter {
        public:
            virtual double getAltitude() = 0;
        };

        class Thermometer {
        public:
            virtual double getTemperature() = 0;
        };

    }
}