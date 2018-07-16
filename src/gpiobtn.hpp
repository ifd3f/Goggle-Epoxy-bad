#include "input.hpp"

#define QUAD_ENCODER_SEQ 0b01100011
#define QUAD_ENCODER_COUNTER 0b00010001

using namespace epoxy;

namespace epoxy {
    namespace devices {

        class GPIOButton : public input::Button {
            const int pin;
            const bool invert;
        public:
            GPIOButton(int id, int pin);
            GPIOButton(int id, int pin, bool invert);
            void initialize() override;
            bool isPressed() override;
        };

        /**
         * A generic quadrature encoder that is read from 2 pins.
         * I have no idea why I'm even bothering with memory efficiency, it's not
         * even an Arduino!
         */
        class GPIOQuadEncoder : public input::Encoder {
            const int pinA, pinB;
            /**
             * 4: 1 for +, 0 for -
             * 7,8: last state (1,2,3,4)
             */
            unsigned char lastState;
            long ticks;
        public:
            GPIOQuadEncoder(int id, int pinA, int pinB);
            void initialize() override;
            void update(int dt) override;
            long getTicks() override;
            void reset() override;
        };

    }
}