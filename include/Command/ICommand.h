#ifndef _20240227224642
#define _20240227224642

// command interface
class ICommand
{
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
};

#endif