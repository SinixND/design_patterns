#ifndef SINGLETON_H_20231129164025
#define SINGLETON_H_20231129164025

#include <mutex>

// included as an example of a parameterized macro
#define DISALLOW_COPY_AND_ASSIGN(T) \
    T(const T&) = delete;           \
    T& operator=(const T&) = delete;

class Singleton
{
public:
    static int getID();

    // get singleton instance
    static Singleton* getInstance();

    // delete copy constructor
    // Singleton(Singleton& other) = delete;
    // delete assignment operator
    // void operator=(const Singleton&) = delete;

private:
    static int counter_;
    static Singleton* singleton_;
    static std::mutex mutex_;

    // make ctor private
    Singleton(){};
    // make dtor private
    ~Singleton(){};

    DISALLOW_COPY_AND_ASSIGN(Singleton);
};

#endif
