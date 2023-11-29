#include "Singleton.h"

#include <iostream>

int Singleton::counter_{0};
Singleton* Singleton::singleton_{nullptr};
std::mutex Singleton::mutex_;

int Singleton::getID() { return counter_; }

Singleton* Singleton::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::cout << "Request singleton instance...\n";

    if (singleton_ == nullptr)
    {
        std::cout << "-> Instantiate Singleton\n";

        singleton_ = new Singleton();

        ++counter_;
    }

    return singleton_;
}
