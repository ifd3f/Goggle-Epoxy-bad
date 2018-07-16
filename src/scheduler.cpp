#include "scheduler.hpp"

#include <algorithm>
#include <iostream>


using namespace epoxy::scheduler;

Command::Command(): state(CommandState::UNINITIALIZED) {
    
}

void Command::setCommandState(CommandState state) { 
    this->state = state; 
}

CommandState Command::getCommandState() {
    return state;
}

SynchronousScheduler::SynchronousScheduler() {
    
}

void SynchronousScheduler::addCommand(Command *cmd) {
    cmd->setCommandState(CommandState::UNINITIALIZED);
    commands.push_back(cmd);
}

void SynchronousScheduler::update(int dt) {
    for (auto cmd: commands) {
        switch (cmd->getCommandState()) {
            case CommandState::UNINITIALIZED:
                cmd->setCommandState(CommandState::RUNNING);
                cmd->initialize();
            break;
            case CommandState::RUNNING:
                cmd->update(dt);
                if (cmd->shouldTerminate()) {
                    cmd->terminate();
                    cmd->setCommandState(CommandState::STOPPED);
                }
            break;
            default:
            break;
        }
    }
    commands.erase(std::remove_if(commands.begin(), commands.end(), [](auto cmd) {
        return cmd->getCommandState() == CommandState::STOPPED;
    }), commands.end());

}