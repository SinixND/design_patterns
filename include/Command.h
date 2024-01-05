#ifndef COMMAND_H_20231126191046
#define COMMAND_H_20231126191046

#include <vector>

// existing receiver can inherit from IReceiver
class IReceiver
{
public:
    virtual void action();
};

// acting instance actually does something,
// probably exists already
class Receiver : public IReceiver
{
public:
    void action() override;
};

// command interface
class ICommand
{
public:
    virtual void execute() const = 0;
};

// implements a concrete command; has information about receiver
class Command : public ICommand
{
private:
    IReceiver& receiver_;

public:
    Command(IReceiver& actor);
    void execute() const override;
};

// processes commands; has information on abstract command;
// probably exists already
class Invoker
{
public:
    void executeCommand(ICommand& command);
    void queueCommand(ICommand& command);
    void executeQueue();

private:
    std::vector<std::reference_wrapper<ICommand>> queue{};
    //* std::vector<ICommand*> queue;
};

#endif