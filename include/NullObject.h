#ifndef NULLOBJECT_H_20231129003459
#define NULLOBJECT_H_20231129003459

#include "Command.h"

// implements a null object; used as concrete command
class NullObject : public ICommand
{
public:
    void execute() override;
};

#endif