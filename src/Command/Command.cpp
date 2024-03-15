#include "Command.h"
#include "Receiver.h"

Command::Command(const Receiver& receiver, int arg)
    : receiver_(receiver)
    , arg_(arg)
{
}

void Command::execute()
{
    receiver_.action(arg_);
}
