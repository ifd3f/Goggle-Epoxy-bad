#pragma once

#include "declarations.hpp"

#include "scheduler.hpp"
#include "activity.hpp"
#include "motion.hpp"
#include "hardware.hpp"
#include "Assets.hpp"

#include <memory>


using namespace epoxy;
namespace epoxy {

    class Context {
    public:
        Context();
        ~Context();

        Assets res;
        Hardware hw;
        activities::ActivityManager* activityManager;
        scheduler::Scheduler* scheduler;
        motion::OrientationIntegrator* orientation;
        input::InputManager* input;
        void run();
    };

}