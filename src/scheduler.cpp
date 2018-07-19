#include "scheduler.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

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

void SynchronousScheduler::runCommand(Command* cmd) {
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

CommandQueue::CommandQueue() {

}

CommandQueue::~CommandQueue() {
    while (first != nullptr) {
        auto* tmp = first;
        first = tmp->next;
        delete tmp;
    }
}

void CommandQueue::pushFront(Command* cmd) {
    Node* second = first;
    first = new Node { nullptr, second, cmd };
    if (second == nullptr) {
        last = first;
    } else {
        second->prev = first;
    }
}

void CommandQueue::pushBack(Command* cmd) {
    auto* penult = last;
    last = new Node { penult, nullptr, cmd };
    if (penult == nullptr) {
        first = last;
    } else {
        penult->next = last;
    }
}

Command* CommandQueue::popFront() {
    if (first == nullptr) {
        return nullptr;
    }
    auto* tmp = first;
    first = tmp->next;
    auto* out = tmp->command;
    delete tmp;
    return out;
}

Command* CommandQueue::Node::remove() {
    if (prev != nullptr) {
        prev->next = next;
    }
    if (next != nullptr) {
        next->prev = prev;
    }
    auto* out = command;
    delete this;
    return out;
}
