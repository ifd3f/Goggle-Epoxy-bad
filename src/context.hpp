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
        Context();
        ~Context();

        Hardware hw;
        activity::ActivityManager* activityManager;
        scheduler::Scheduler* scheduler;
        motion::OrientationIntegrator* orientation;
        void run();
    };

}