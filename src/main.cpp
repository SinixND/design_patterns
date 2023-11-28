#include "Command.h"
#include "NullObject.h"
#include <iostream>
#include <memory>

int main(/* int argc, char **argv */)
{
    // Command Pattern
    // ================================
    Receiver receiver; // = std::make_shared<Receiver>();

    auto command = std::make_shared<ConcreteCommand>(receiver);

    Invoker invoker;

    // invoker.executeCommand(command);

    invoker.queueCommand(command);
    invoker.executeQueue();
    // ================================

    // Null Object Pattern
    // ================================
    auto nullCommand = std::make_shared<NullObject>();

    invoker.executeCommand(nullCommand);
    // ================================

    return 0;
}
