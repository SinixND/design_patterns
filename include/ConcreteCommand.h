#ifndef _20240227225014
#define _20240227225014

#include "ICommand.h"
#include "Receiver.h"

// implements a concrete command; has information about receiver
class ConcreteCommand : public ICommand
{
private:
    Receiver receiver_;
    int arg_;

public:
    ConcreteCommand(const Receiver& actor, int arg);
    void execute() override;
};

#endif