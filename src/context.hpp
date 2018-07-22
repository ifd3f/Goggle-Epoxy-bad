#pragma once

#include <memory>
#include "scheduler.hpp"
#include "activity.hpp"
#include "motion.hpp"
#include "hardware.hpp"
#include "Assets.hpp"


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