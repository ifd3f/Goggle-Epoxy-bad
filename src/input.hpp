#pragma once

#include <queue>
#include <vector>
#include <memory>

#include "scheduler.hpp"

using namespace epoxy::scheduler;
namespace epoxy {
    namespace input {
        using namespace epoxy::input;

        class Button : public Command {
        public:
            Button(int id);
            virtual ~Button() {};
            const int id;
            virtual bool isPressed() = 0;
        };

        class Encoder : public Command {
        public:
            Encoder(int id);
            virtual ~Encoder() {};
            const int id;
            virtual void reset() = 0;
            virtual long getTicks() = 0;
        };

        /**
         * Represents a change in button state.
         */
        struct ButtonEvent {
            Button* btn;
            /**
             * true indicates it was just pressed, false indicates it was just released.
             */
            bool state;
        };
        
        struct EncoderEvent {
            Encoder* enc;
            /**
             * 1 indicates it went forward, -1 indicates it went backward.
             */
            signed char delta;
        };
        
        class ButtonListener : public Command {
            std::shared_ptr<std::queue<ButtonEvent>> queue;
            std::shared_ptr<Button> btn;
            bool last;
        public:
            ButtonListener(std::shared_ptr<Button> btn);
            void update(int dt) override;
            void attachEventQueue(std::shared_ptr<std::queue<ButtonEvent>> queue);
        };

        class EncoderListener : public Command {
            std::shared_ptr<std::queue<EncoderEvent>> queue;
            std::shared_ptr<Encoder> enc;
            long last;
        public:
            EncoderListener(std::shared_ptr<Encoder> enc);
            void update(int dt) override;
            void attachEventQueue(std::shared_ptr<std::queue<EncoderEvent>> queue);
        };

    }
}