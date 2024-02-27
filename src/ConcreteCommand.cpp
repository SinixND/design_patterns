#include "ConcreteCommand.h"
#include "Receiver.h"

ConcreteCommand::ConcreteCommand(const Receiver& receiver, int arg)
    : receiver_(receiver)
    , arg_(arg)
{
}

void ConcreteCommand::execute()
{
    receiver_.action(arg_);
}
