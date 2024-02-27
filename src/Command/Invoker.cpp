#include "Invoker.h"

void Invoker::executeCommand(std::shared_ptr<ICommand> command)
{
    command->execute();
}

void Invoker::queueCommand(std::shared_ptr<ICommand> command)
{
    //* queue.push_back(command);
    queue.push(command);
}

void Invoker::executeQueue()
{
    while (!queue.empty())
    {
        queue.front()->execute();
        queue.pop();
    }
}