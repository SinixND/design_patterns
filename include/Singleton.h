#ifndef SINGLETON_H_20231129164025
#define SINGLETON_H_20231129164025

#include <mutex>


/*
The Singleton's constructor/destructor should always be private to
prevent direct construction/desctruction calls with the `new`/`delete`
operator.

Singletons should not be cloneable.

Singletons should not be assignable.
*/

class Singleton
{
public:
    // delete copy constructor
    Singleton(Singleton &other) = delete;
    // delete assignment operator
    void operator=(const Singleton &) = delete;

    // get singleton instance
    static Singleton* getInstance();

private:
    static Singleton* singleton_;
    static std::mutex mutex_;

    // private constructor!
    Singleton() { };
    ~Singleton() {};
};

#endif
