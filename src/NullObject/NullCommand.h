#ifndef NULLCOMMAND_H_20231129003459
#define NULLCOMMAND_H_20231129003459

#include "ICommand.h"
#include <iostream>

// implements a null object; used as concrete command
class NullCommand : public ICommand
{
public:
    void execute() override
    {
        std::cout << "NullCommand does nothing...\n";
    }
};

#endif