#include "ConcreteCommand.h"
#include "ICommand.h"
#include "Invoker.h"
#include "NullObject.h"
#include "Receiver.h"
#include "Singleton.h"
#include <iostream>
#include <memory>
#include <thread>

// Singleton Pattern
// ================================
void ThreadFoo()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
    std::cout << "Singleton count: " << singleton->getID() << "\n";
}

void ThreadBar()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
    std::cout << "Singleton count: " << singleton->getID() << "\n";
}
// ================================

int main(/* int argc, char **argv */)
{
    // Command Pattern
    // ================================
    std::cout << "\nBegin section: Command pattern\n\n";

    Receiver receiver;

    auto command{std::make_shared<ConcreteCommand>(receiver, 5)};

    Invoker invoker;

    // invoker.executeCommand(command);
    invoker.queueCommand(command);
    invoker.queueCommand(command);
    invoker.executeQueue();

    std::cout << "\nEnd section: Command pattern\n\n";
    // ================================

    // Null Object Pattern
    // ================================
    std::cout << "\nBegin section: Null Object pattern\n\n";

    invoker.executeCommand(std::make_shared<NullObject>());

    std::cout << "\nEnd section: Null Object pattern\n\n";
    // ================================

    // Singleton Pattern
    // ================================
    std::cout << "\nBegin section: Singleton pattern\n\n";

    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);

    t1.join();
    t2.join();

    std::cout << "\nEnd section: Singleton pattern\n\n";
    // ================================

    return 0;
}
