#include "activity.hpp"

#include <memory>

using namespace epoxy::activities;

void Activity::onStart() {

}

void Activity::onResume() {

}

void Activity::onUpdate(int dt) {

}

void Activity::onSuspend() {

}

void Activity::onStop() {

}

ActivityManager::ActivityManager(Context* ctx) {
    this->ctx = ctx;
}

void ActivityManager::initialize() {

}

void ActivityManager::update(int dt) {
    switch (nextOperation.op) {
        case PUSH:
            if (currentActivity != nullptr) {
                currentActivity->onSuspend();
            }
            stack.push(currentActivity);
            currentActivity = nextOperation.activity;
            currentActivity->ctx = ctx;
            currentActivity->onStart();
            currentActivity->onResume();
        break;
        case POP:
            currentActivity->onSuspend();
            currentActivity->onStop();
            currentActivity = stack.top();
            stack.pop();
            currentActivity->onResume();
        break;
        case SWAP:
            currentActivity->onSuspend();
            currentActivity->onStop();
            currentActivity = nextOperation.activity;
            currentActivity->ctx = ctx;
            currentActivity->onStart();
            currentActivity->onResume();
        break;
        default:
        break;
    }

    nextOperation = { NONE, nullptr };
    currentActivity->onUpdate(dt);
}

void ActivityManager::pushActivity(std::shared_ptr<Activity> activity) {
    nextOperation = { PUSH, activity };
}

void ActivityManager::popActivity() {
    nextOperation = { POP, nullptr };
}

void ActivityManager::swapActivity(std::shared_ptr<Activity> activity) {
    nextOperation = { SWAP, activity };
}

