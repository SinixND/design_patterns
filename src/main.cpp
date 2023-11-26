#include "Command.h"

#include <iostream>
#include <memory>

int main(/* int argc, char **argv */)
{
    // Command
    // ================================
    auto receiver = std::make_shared<Receiver>();

    auto command = std::make_shared<ConcreteCommand>(receiver);

    Invoker invoker;

    // invoker.executeCommand(command);
    invoker.queueCommand(command);
    invoker.executeQueue();
    // ================================

    return 0;
}
