#include "Command.h"

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
    int nThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(nThreads);

    int nCommands = queue.size();
    int iterations = (nThreads < nCommands) ? nThreads : nCommands;

    for (int i{0}; i < iterations; ++i)
    {
        threads[i] = std::thread(
            [this]
            {
                queue.front()->execute();
                queue.erase(queue.begin());
            });
    }

    for (int i{0}; i < iterations; ++i)
    {
        if (threads[i].joinable())
            threads[i].join();
    }
}

ConcreteCommand::ConcreteCommand(std::shared_ptr<Receiver> receiver)
    : receiver_(receiver)
{
}

void ConcreteCommand::execute() { receiver_->doSomething(); }