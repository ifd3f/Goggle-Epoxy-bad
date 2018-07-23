#pragma once

#include "declarations.hpp"

#include "scheduler.hpp"
#include "context.hpp"

#include <memory>
#include <stack>

namespace epoxy {
    namespace activities {
        
        class Activity {
        protected:
            epoxy::Context* ctx;
        public:
            virtual ~Activity() = default;
            
            virtual void onStart();
            virtual void onResume();
            virtual void onUpdate(int dt);
            virtual void onSuspend();
            virtual void onStop();

            friend class ActivityManager;
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
            Context* ctx;
        public:
            ActivityManager(Context *ctx);

            void initialize() override;
            void update(int dt) override;

            void pushActivity(std::shared_ptr<Activity> activity);
            void popActivity();
            void swapActivity(std::shared_ptr<Activity> activity);
        };

    }
}