#include "scheduler.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

#include "util/util.hpp"

using namespace epoxy::scheduler;

Command::Command(): state(CommandState::UNINITIALIZED) {
    
}

void Command::setCommandState(CommandState state) { 
    this->state = state; 
}

CommandState Command::getCommandState() {
    return state;
}

long long Command::getLastExecuted() {
    return lastExecuted;
}

void Command::doLoop(long long time) {
    switch (getCommandState()) {
        case CommandState::UNINITIALIZED:
            setCommandState(CommandState::RUNNING);
            initialize();
            break;
        case CommandState::RUNNING:
            update(static_cast<int>(time - lastExecuted));
            if (shouldTerminate()) {
                terminate();
                setCommandState(CommandState::STOPPED);
            }
            break;
        case CommandState::STOPPED:
            break;
    }
    lastExecuted = time;
}

void Command::initialize() {

}

void Command::update(int dt) {

}

bool Command::shouldTerminate() {
    return false;
}

void Command::terminate() {

}

SynchronousScheduler::SynchronousScheduler() = default;

void SynchronousScheduler::addCommand(Command *cmd) {
    cmd->setCommandState(CommandState::UNINITIALIZED);
    standard.push_back(cmd);
    if (cmd->scheduling.repTime > 0) {
        priority.push_back(standard.end());
    }
}

void SynchronousScheduler::update() {
    auto* cmd = standard.front();
    standard.pop_front();
    cmd->doLoop(util::getMillis());
    if (cmd->getCommandState() != CommandState::STOPPED) {
        standard.push_back(cmd);
    }
}
