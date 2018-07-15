#pragma once

#include <memory>
#include "scheduler.hpp"
#include "activity.hpp"
#include "motion.hpp"

namespace epoxy {

    class Context {
    public:
        Context();
        std::unique_ptr<activity::ActivityManager> activityManager;
        std::unique_ptr<scheduler::Scheduler> scheduler;
        std::unique_ptr<motion::OrientationIntegrator> orientation;
    };

}