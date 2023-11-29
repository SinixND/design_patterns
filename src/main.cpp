#include "Command.h"
#include "NullObject.h"
#include "Singleton.h"
#include <iostream>
#include <memory>
#include <thread>

// Singleton Pattern
// ================================
void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
}

void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
}
// ================================

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

    // Singleton Pattern
    // ================================
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    // ================================

    return 0;
}
