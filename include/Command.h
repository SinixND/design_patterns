#ifndef COMMAND_H_20231126191046
#define COMMAND_H_20231126191046

#include <vector>

// command interface
class AbstractCommand
{
public:
    virtual ~AbstractCommand();
    virtual void execute();
};

class Receiver
{
public:
    virtual void doSomething();
    virtual ~Receiver();
};

// acting instance actually does something
class concReceiver : public Receiver
{
public:
    void doSomething() override;
};

// processes commands; has information on abstract command
class Invoker
{
public:
    void executeCommand(AbstractCommand& command);
    void queueCommand(AbstractCommand* command);
    void executeQueue();

private:
    // std::vector<std::reference_wrapper<AbstractCommand>> queue;
    std::vector<AbstractCommand*> queue;
};

// implements a concrete command; has information about receiver
class ConcreteCommand : public AbstractCommand
{
private:
    Receiver& receiver_;

public:
    ConcreteCommand(Receiver& actor);
    void execute() override;
};

#endif