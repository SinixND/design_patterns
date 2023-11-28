#include "Command.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <thread>

AbstractCommand::~AbstractCommand() {}
void AbstractCommand::execute() {}

void Receiver::doSomething() { std::cout << "Actor does something\n"; }

void Invoker::executeCommand(std::shared_ptr<AbstractCommand> command)
{
    command->execute();
}

void Invoker::queueCommand(std::shared_ptr<AbstractCommand> command)
{
    queue.push_back(command);
}

void Invoker::executeQueue()
{
    while (!queue.empty())
    {
        queue.front()->execute();
        queue.erase(queue.begin());
    }
}

ConcreteCommand::ConcreteCommand(Receiver& receiver)
    : receiver_(receiver)
{
}

void ConcreteCommand::execute() { receiver_.doSomething(); }