#pragma once

#include <queue>
#include <vector>
#include <memory>

#include "scheduler.hpp"

using namespace epoxy;
namespace epoxy {
    namespace input {

        class Button : public scheduler::Command {
        public:
            Button(int id);
            virtual ~Button() = default;
            const int id;
            virtual bool isPressed() = 0;
        };

        class Encoder : public scheduler::Command {
        public:
            explicit Encoder(int id);
            virtual ~Encoder() = default;
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
        
        class ButtonQueueListener : public scheduler::Command {
            Button* btn;
            std::queue<ButtonEvent>* queue;
            bool last;
        public:
            ButtonQueueListener(Button* btn, std::queue<ButtonEvent>* queue);
            void update(int dt) override;
            void terminate() override;
        };

        class EncoderQueueListener : public scheduler::Command {
            Encoder* enc;
            std::queue<EncoderEvent>* queue;
            long last;
        public:
            EncoderQueueListener(Encoder* enc, std::queue<EncoderEvent>* queue);
            void update(int dt) override;
            void terminate() override;
        };

        class InputListener {
        public:
            virtual void onInput(EncoderEvent ev) {};
            virtual void onInput(ButtonEvent ev) {};
        };

        class InputManager : public scheduler::Command {
            std::queue<EncoderEvent> eQueue;
            std::queue<ButtonEvent> bQueue;
            scheduler::Scheduler* sched;
            InputListener* listener;
        public:
            InputManager(scheduler::Scheduler* sched);

            void update(int dt) override;

            void addButton(Button* btn);
            void addEncoder(Encoder* enc);
            void setInputListener(InputListener* listener);
        };

    }
}