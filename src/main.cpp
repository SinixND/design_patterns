#include "Command.h"
#include "Event.h"
#include "Invoker.h"
#include "NullCommand.h"
#include "Observer.h"
#include "Receiver.h"
#include "Singleton.h"
#include "Subject.h"
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

    auto command{std::make_shared<Command>(receiver, 5)};

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

    invoker.executeCommand(std::make_shared<NullCommand>());

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

    // Subscriber Pattern
    // ================================
    std::cout << "\nBegin section: Observer pattern\n\n";

    Publisher publisher{};
    std::shared_ptr<Subscriber> subscriber1{std::make_shared<Subscriber>(Event::event0)};
    std::shared_ptr<Subscriber> subscriber2{std::make_shared<Subscriber>(Event::event1)};

    publisher.addSubscriber(subscriber1);
    publisher.addSubscriber(subscriber2);

    // Send messages to every subscriber for this publisher, regardless
    // of the 'Event'
    publisher.notifyAll();
    std::cout << "\n";

    // Notify any subscriber that has to do with specified event
    publisher.notify(Event::event0);
    std::cout << "\n";

    publisher.removeSubscriber(subscriber1);

    publisher.notifyAll();
    std::cout << "\n";
    publisher.notify(Event::event0);

    std::cout << "\nEnd section: Observer pattern\n\n";
    // ================================

    return 0;
}
