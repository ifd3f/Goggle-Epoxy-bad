#include "scheduler.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

#include <boost/date_time.hpp>

using namespace epoxy::scheduler;

Command::Command(): state(CommandState::UNINITIALIZED) {
    
}

void Command::setCommandState(CommandState state) { 
    this->state = state; 
}

CommandState Command::getCommandState() {
    return state;
}

unsigned long long Command::getLastExecuted() {
    return lastExecuted;
}

void Command::doLoop(unsigned long long time) {
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

SynchronousScheduler::SynchronousScheduler() = default;

void SynchronousScheduler::addCommand(Command *cmd) {
    cmd->setCommandState(CommandState::UNINITIALIZED);
    if (cmd->scheduling.minTime > 0) {
        lq.push_back(cmd);
    } else if (cmd->scheduling.repTime > 0) {
        hq.push_back(cmd);
    } else {
        sq.push_back(cmd);
    }
}

void SynchronousScheduler::update() {
    for (auto cmd: lq) {
        //if (cmd->scheduling.repTime - ;
    }
}
