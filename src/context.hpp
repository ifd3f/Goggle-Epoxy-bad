#pragma once

#include <memory>
#include "scheduler.hpp"
#include "activity.hpp"
#include "motion.hpp"
#include "hardware.hpp"


using namespace epoxy;
namespace epoxy {

    class Context {
    public:
        Hardware hw;
        activity::ActivityManager* activityManager;
        scheduler::Scheduler* scheduler;
        motion::OrientationIntegrator* orientation;
        Context();
        void run();
        ~Context();
    };

}