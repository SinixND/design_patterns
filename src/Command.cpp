#include "Command.h"

#include <iostream>

void IReceiver::action() {}

void Receiver::action() { std::cout << "Actor does something\n"; }

void ICommand::execute() const {}

Command::Command(IReceiver& receiver)
    : receiver_(receiver)
{
}

void Command::execute() const
{
    receiver_.action();
}

void Invoker::executeCommand(ICommand& command)
{
    command.execute();
}

void Invoker::queueCommand(ICommand& command)
{
    queue.push_back(command);
}

void Invoker::executeQueue()
{
    while (!queue.empty())
    {
        // queue.front().execute();
        queue.front().get().execute();
        queue.erase(queue.begin());
    }
}
