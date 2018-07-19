#pragma once

#include <vector>

namespace epoxy {
    namespace scheduler {
        enum class CommandState { 
            UNINITIALIZED, RUNNING, STOPPED
        };

        class Command {
            CommandState state;
        public:
            Command();
            virtual ~Command() {};
            virtual void initialize() { };
            virtual void update(int dt) { };
            virtual bool shouldTerminate() { return false; };
            virtual void terminate() { };

            void setCommandState(CommandState state);
            CommandState getCommandState();
        };

        class Scheduler {
        public:
            virtual ~Scheduler() {};
            virtual void addCommand(Command *cmd) = 0;
            virtual void update(int dt) = 0;
        };

        class SynchronousScheduler : public Scheduler {
            std::vector<Command*> commands;
        public:
            SynchronousScheduler();
            void addCommand(Command *cmd) override;
            void update(int dt) override;
        };

    }
}