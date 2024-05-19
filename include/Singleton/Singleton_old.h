#ifndef SINGLETON_H_20231129164025
#define SINGLETON_H_20231129164025

#include <iostream>
#include <mutex>

// included as an example of a parameterized macro
#define DISALLOW_COPY_AND_ASSIGN(T) \
    T(const T&) = delete;           \
    T& operator=(const T&) = delete;

namespace dtb
{
    static int id{};
}

class Singleton
{
public:
    static inline int getID() { return counter_; };

    // Singleton attributes
    //=================================
    // get singleton instance
    static inline Singleton* getInstance()
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
    };

    // Delete Singleton instance
    static inline void deleteInstance()
    {
        delete singleton_;
    };
    //=================================

private:
    static inline int counter_{0};

    // Singleton attributes
    //=================================
    static inline Singleton* singleton_{nullptr};
    static inline std::mutex mutex_{};

    // make ctor private
    Singleton(){};
    // make dtor private
    ~Singleton(){};

    DISALLOW_COPY_AND_ASSIGN(Singleton)
    //=================================
};

#endif
