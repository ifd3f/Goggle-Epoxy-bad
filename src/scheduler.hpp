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
            long long lastExecuted = 0;
        public:
            Command();
            virtual ~Command() = default;

            /**
             * NYI
             */
            const CommandSchedulingParam scheduling;

            virtual void initialize();
            virtual void update(int dt);
            virtual bool shouldTerminate();
            virtual void terminate();

            void setCommandState(CommandState state);
            CommandState getCommandState();
            long long int getLastExecuted();
            void doLoop(long long time);
        };

        class Scheduler {
        public:
            virtual ~Scheduler() = default;
            virtual void addCommand(Command *cmd) = 0;
            virtual void update() = 0;
        };


        class SynchronousScheduler : public Scheduler {
            std::list<Command*> standard;
            std::list<Command*> waiting;
            std::list<std::list<Command*>::iterator> priority;

            unsigned long nextScanPriority;
        public:
            SynchronousScheduler();
            void addCommand(Command *cmd) override;
            void update() override;
        };

    }
}