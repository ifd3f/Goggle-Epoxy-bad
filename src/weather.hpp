namespace epoxy {
    namespace weather {

        class Barometer {
        public:
            virtual double getPresure() = 0;
        };

        class Altimeter {
        public:
            virtual double getAltimeter() = 0;
        };

        class Thermometer {
        public:
            virtual double getTemperature() = 0;
        };

    }
}