#include "Command.h"
#include "Event.h"
#include "Invoker.h"
#include "NullCommand.h"
#include "Publisher.h"
#include "Receiver.h"
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
    NullSingleton& singleton = NullSingleton::instance();
    std::cout << "ThreadFoo: Singleton address: " << &singleton << "\n";
}

void ThreadBar()
{
    std::cout << "ThreadBar: Enter\n";
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    NullSingleton& singleton = NullSingleton::instance();
    std::cout << "ThreadBar: Singleton address: " << &singleton << "\n";
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

    // Observer Pattern
    // ================================
    std::cout << "\n Begin section: Observer pattern\n\n";

    Publisher publisher{};
    std::shared_ptr<Subscriber> subscriber1{std::make_shared<Subscriber>(Event::null)};

    std::cout << "[main] Add subscriber " << subscriber1 << " to publisher\n";
    publisher.addSubscriber(subscriber1);

    std::cout << "[main] Add annonymous subscriber (without object) to publisher\n";
    publisher.addSubscriber(std::make_shared<Subscriber>(Event::event1));

    // Send messages to every subscriber for this publisher, regardless of event
    std::cout << "[main] Notify all subscribers\n";
    publisher.notifyAll();
    std::cout << "\n";

    // Notify subscribers that registered to specific event
    std::cout << "[main] Notify all subscribers about fired event\n";
    publisher.notify(Event::null);
    std::cout << "\n";

    // Remove subscriber
    std::cout << "[main] Remove subscriber from publisher\n";
    publisher.removeSubscriber(subscriber1);

    // Send messages to every subscriber for this publisher, regardless of event
    std::cout << "[main] Notify all subscribers\n";
    publisher.notifyAll();
    std::cout << "\n";

    std::cout << "\n End section: Observer pattern\n\n";
    // ================================

    return 0;
}
