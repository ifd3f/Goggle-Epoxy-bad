#pragma once

#include "scheduler.hpp"

#include <stack>

namespace epoxy {
    namespace activity {

        class Activity {
        public:
            virtual ~Activity();
            
            bool shouldDelete = true;
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
            Activity* activity;
        };

        class ActivityManager : public scheduler::Command {
            std::stack<Activity*> stack;
            Activity* currentActivity = nullptr;
            ActivityOperation nextOperation;
        public:
            ActivityManager();

            void initialize() override;
            void update(int dt) override;

            void pushActivity(Activity* activity);
            void popActivity();
            void swapActivity(Activity* activity);
        };
    }
}