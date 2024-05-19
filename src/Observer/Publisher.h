#ifndef IG20240520003332
#define IG20240520003332

#include "IPublisher.h"

class Publisher : public IPublisher
{
public:
    // Original function that should be listened to
    void originalFunction()
    {
        // I do something meaningful
    }

    // Function becomes a functor
    void operator()()
    {
        // Original function that should be listened to
        originalFunction();
        notifyAll();
    }
};

#endif