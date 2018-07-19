#include "context.hpp"

#include "scheduler.hpp"
#include "activity.hpp"
#include "motion.hpp"
#include "hardware.hpp"

using namespace epoxy;


Context::Context() {
    scheduler = new scheduler::SynchronousScheduler();
    activityManager = new activity::ActivityManager();
    orientation = new motion::OrientationIntegrator(hw.gyro, hw.acc, hw.mag, 0.02);

    scheduler->addCommand(activityManager);
    scheduler->addCommand(orientation);
    scheduler->addCommand(hw.gyro);
    scheduler->addCommand(hw.acc);
    scheduler->addCommand(hw.btnH);
    scheduler->addCommand(hw.btnX);
    scheduler->addCommand(hw.btnY);
    scheduler->addCommand(hw.btnZ);
    scheduler->addCommand(hw.encoder);
    scheduler->addCommand(hw.screen);
}

void Context::run() {
    while (true) {
        scheduler->update(1);
    }
}

Context::~Context() {
    delete scheduler;
    delete activityManager;
    delete orientation;
}