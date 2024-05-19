#include "Command.h"
#include "Event.h"
#include "Invoker.h"
#include "NullCommand.h"
#include "Publisher.h"
#include "Receiver.h"
#include "Singleton.h"
#include "Subscriber.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// Singleton Pattern
// ================================
void ThreadFoo()
{
    std::cout << "ThreadFoo: Enter\n";
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
    std::cout << "ThreadFoo: Singleton count: " << singleton->getID() << "\n";
    std::cout << "ThreadFoo: Static address: " << &dtb::id << "\n";
}

void ThreadBar()
{
    std::cout << "ThreadBar: Enter\n";
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Singleton* singleton = Singleton::getInstance();
    std::cout << "ThreadBar: Singleton count: " << singleton->getID() << "\n";
    std::cout << "ThreadBar: Static address: " << &dtb::id << "\n";
}
// ================================

int main(/* int argc, char **argv */)
{
    // Command Pattern
    // ================================
    std::cout << "\n Begin section: Command pattern\n\n";

    Receiver receiver;

    auto command{std::make_shared<Command>(receiver, 5)};

    Invoker invoker;

    // invoker.executeCommand(command);
    invoker.queueCommand(command);
    invoker.queueCommand(command);
    invoker.executeQueue();

    std::cout << "\n End section: Command pattern\n\n";
    // ================================

    // Null Object Pattern
    // ================================
    std::cout << "\n Begin section: Null Object pattern\n\n";

    invoker.executeCommand(std::make_shared<NullCommand>());

    std::cout << "\n End section: Null Object pattern\n\n";
    // ================================

    // Singleton Pattern
    // ================================
    std::cout << "\n Begin section: Singleton pattern\n\n";

    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);

    t1.join();
    t2.join();

    std::cout << "\n End section: Singleton pattern\n\n";
    // ================================

    // Subscriber Pattern
    // ================================
    std::cout << "\n Begin section: Observer pattern\n\n";

    std::shared_ptr<Subscriber> subscriber1{std::make_shared<Subscriber>(Event::event0)};
    std::shared_ptr<Subscriber> subscriber2{std::make_shared<Subscriber>(Event::event1)};
    Publisher publisher{};

    std::cout << "[main] Add subscriber " << static_cast<int>(subscriber1->event) << " to publisher\n";
    publisher.addSubscriber(subscriber1);

    std::cout << "[main] Add subscriber " << static_cast<int>(subscriber2->event) << " to publisher\n";
    publisher.addSubscriber(subscriber2);

    // Send messages to every subscriber for this publisher, regardless
    // of the 'Event'
    // std::cout << "[main] Notify all subscribers from publisher\n";
    // publisher.notifyAll();
    // std::cout << "\n";

    std::cout << "[main] Call publisher function\n";
    publisher();
    std::cout << "\n";

    // Notify any subscriber that has to do with specified event
    std::cout << "[main] Notify subscribers for event " << static_cast<int>(Event::event0) << " from publisher\n";
    publisher.notify(Event::event0);
    std::cout << "\n";

    std::cout << "[main] Remove subscriber " << static_cast<int>(subscriber1->event) << " from publisher\n";
    publisher.removeSubscriber(subscriber1);

    std::cout << "[main] Notify all subscribers from publisher\n";
    publisher.notifyAll();
    std::cout << "\n";

    std::cout << "[main] Notify subscribers for event " << static_cast<int>(Event::event0) << " from publisher\n";
    publisher.notify(Event::event0);

    std::cout << "\n End section: Observer pattern\n\n";
    // ================================

    return 0;
}
