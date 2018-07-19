#pragma once

#include <iterator>
#include <list>
#include <vector>

namespace epoxy {
    namespace scheduler {
        enum class CommandState { 
            UNINITIALIZED, RUNNING, STOPPED
        };

        struct CommandSchedulingParam {
            /**
             * Minimum amount of time that must pass before next update.
             */
            int minTime = -1;
            /**
             * Maximum amount of time that can pass after last update.
             */
            int repTime = -1;
        };

        class Scheduler;

        class Command {
            CommandState state;
            unsigned long long lastExecuted;
        public:
            Command();
            virtual ~Command() = default;

            const CommandSchedulingParam scheduling;

            virtual void initialize() { };
            virtual void update(int dt) { };
            virtual bool shouldTerminate() { return false; };
            virtual void terminate() { };

            void setCommandState(CommandState state);
            CommandState getCommandState();
            unsigned long long getLastExecuted();
            void doLoop(unsigned long long time);
        };

        class Scheduler {
        public:
            virtual ~Scheduler() = default;
            virtual void addCommand(Command *cmd) = 0;
            virtual void update() = 0;
        };


        class SynchronousScheduler : public Scheduler {
            std::list<Command*> sq, hq, lq;
        public:
            SynchronousScheduler();
            void addCommand(Command *cmd) override;
            void update() override;
        };

    }
}