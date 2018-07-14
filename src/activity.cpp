#include "activity.hpp"

using namespace epoxy::activity;

ActivityManager::ActivityManager() {

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
            currentActivity->onStart();
            currentActivity->onResume();
        break;
        case POP:
            currentActivity->onSuspend();
            currentActivity->onStop();
            if (currentActivity->shouldDelete) {
                delete currentActivity;
            }
            currentActivity = stack.top();
            stack.pop();
            currentActivity->onResume();
        break;
        case SWAP:
            currentActivity->onSuspend();
            currentActivity->onStop();
            if (currentActivity->shouldDelete) {
                delete currentActivity;
            }
            currentActivity = nextOperation.activity;
            currentActivity->onStart();
            currentActivity->onResume();
        break;
        default:
        break;
    }

    nextOperation = { NONE, nullptr };
    currentActivity->onUpdate(dt);
}

void ActivityManager::pushActivity(Activity* activity) {
    nextOperation = { PUSH, activity };
}

void ActivityManager::popActivity() {
    nextOperation = { POP, nullptr };
}

void ActivityManager::swapActivity(Activity* activity) {
    nextOperation = { SWAP, activity };
}

