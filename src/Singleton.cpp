#include "Singleton.h"

#include <iostream>

Singleton* Singleton::singleton_{nullptr};
std::mutex Singleton::mutex_;

Singleton* Singleton::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (singleton_ == nullptr)
    {
        std::cout << "Create new singleton" << std::endl;
        singleton_ = new Singleton();
    }

    return singleton_;
}
