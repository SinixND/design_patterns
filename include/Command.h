#ifndef COMMAND_H_20231126191046
#define COMMAND_H_20231126191046

#include <memory>
#include <vector>

// command interface
class AbstractCommand
{
public:
    virtual ~AbstractCommand();
    virtual void execute();
};

// acting instance actually does something
class Receiver
{
public:
    void doSomething();
};

// processes commands; has information on abstract command
class Invoker
{
public:
    void executeCommand(std::shared_ptr<AbstractCommand> command);
    void queueCommand(std::shared_ptr<AbstractCommand> command);
    void executeQueue();

private:
    std::vector<std::shared_ptr<AbstractCommand>> queue;
};

// implements a concrete command; has information about receiver
class ConcreteCommand : public AbstractCommand
{
private:
    Receiver receiver_;

public:
    ConcreteCommand(Receiver& actor);
    void execute() override;
};

#endif