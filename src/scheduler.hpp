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
            unsigned long lastRun;
        public:
            Command();
            virtual ~Command() {};

            const CommandSchedulingParam scheduling;

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


        class CommandQueue {
        public:
            struct Node {
                Node* prev;
                Node* next;
                Command* command;
                Command* remove();
            };

            CommandQueue();
            ~CommandQueue(); 
            void pushFront(Command* cmd);
            void pushBack(Command* cmd);
            Command* popFront();
            Node* first;
            Node* last;
        };

        class SynchronousScheduler : public Scheduler {
            CommandQueue commands;
            std::list<Command*> priorityCommands;
            void runCommand(Command* cmd);
        public:
            SynchronousScheduler();
            void addCommand(Command *cmd) override;
            void update(int dt) override;
        };

    }
}