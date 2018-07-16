#pragma once

#include "scheduler.hpp"

#include <memory>
#include <stack>

namespace epoxy {
    namespace activity {

        class Activity {
        public:
            virtual ~Activity();
            
            virtual void onInput(int btn, int data) {};
            virtual void onStart() {};
            virtual void onResume() {};
            virtual void onUpdate(int dt) {};
            virtual void onSuspend() {};
            virtual void onStop() {};
        };

        enum ActivityOperationType {
            PUSH, POP, SWAP, NONE
        };

        struct ActivityOperation {
            ActivityOperationType op;
            std::shared_ptr<Activity> activity;
        };

        class ActivityManager : public scheduler::Command {
            std::stack<std::shared_ptr<Activity>> stack;
            std::shared_ptr<Activity> currentActivity = nullptr;
            ActivityOperation nextOperation;
        public:
            ActivityManager();

            void initialize() override;
            void update(int dt) override;

            void pushActivity(std::shared_ptr<Activity> activity);
            void popActivity();
            void swapActivity(std::shared_ptr<Activity> activity);
        };
    }
}