#ifndef _20240227225115
#define _20240227225115

#include "ICommand.h"
#include <memory>
#include <queue>

// processes commands; has information on abstract command;
class Invoker
{
public:
    void executeCommand(std::shared_ptr<ICommand> command)
    {
        command->execute();
    }

    void queueCommand(std::shared_ptr<ICommand> command)
    {
        queue.push(command);
    }

    void executeQueue()
    {
        while (!queue.empty())
        {
            queue.front()->execute();
            queue.pop();
        }
    }

private:
    std::queue<std::shared_ptr<ICommand>> queue;
};

#endif