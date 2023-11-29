#include "Command.h"

#include <iostream>

AbstractCommand::~AbstractCommand() {}
void AbstractCommand::execute() {}

Receiver::~Receiver() {}
void Receiver::doSomething() {}

void concReceiver::doSomething() { std::cout << "Actor does something\n"; }

void Invoker::executeCommand(AbstractCommand& command)
{
    command.execute();
}

void Invoker::queueCommand(AbstractCommand* command)
{
    queue.push_back(command);
}

void Invoker::executeQueue()
{
    while (!queue.empty())
    {
        // queue.front().execute();
        queue.front()->execute();
        queue.erase(queue.begin());
    }
}

ConcreteCommand::ConcreteCommand(Receiver& receiver)
    : receiver_(receiver)
{
}

void ConcreteCommand::execute()
{
    receiver_.doSomething();
}
