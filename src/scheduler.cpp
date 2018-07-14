#include "scheduler.hpp"

#include <algorithm>
#include <iostream>


using namespace epoxy::scheduler;

Command::Command(): state(CommandState::UNINITIALIZED) {
    
}

void Command::setState(CommandState state) { 
    this->state = state; 
}

CommandState Command::getState() {
    return state;
}

SynchronousScheduler::SynchronousScheduler() {
    
}

void SynchronousScheduler::addCommand(Command *cmd) {
    cmd->setState(CommandState::UNINITIALIZED);
    commands.push_back(cmd);
}

void SynchronousScheduler::update(int dt) {
    for (auto cmd: commands) {
        switch (cmd->getState()) {
            case CommandState::UNINITIALIZED:
                cmd->setState(CommandState::RUNNING);
                cmd->initialize();
            break;
            case CommandState::RUNNING:
                cmd->update(dt);
                if (cmd->shouldTerminate()) {
                    cmd->terminate();
                    cmd->setState(CommandState::STOPPED);
                }
            break;
            default:
            break;
        }
    }
    commands.erase(std::remove_if(commands.begin(), commands.end(), [](auto cmd) {
        return cmd->getState() == CommandState::STOPPED;
    }), commands.end());

}