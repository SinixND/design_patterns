# Design Patterns


## Behavioral Patterns


### Command Pattern


#### Description

- Used to make the connection (**Command**) from a trigger (**Invoker**) to an *executable action* (**Receiver**) a *manageable object*.

- Used if *executable action* is shared by multiple **Receivers**


#### Explanation 

**Receiver:**

- Actor whose action is performed
- Action will be called by **ConcreteCommand**
- Multiple receivers might share the same action


**Command (abstract):**

- Is managed by **Invoker**
- Interface for **ConcreteCommands**
- Decouples **ConcreteCommands** from **Invoker**


**Invoker (interface):**

- Must only know about (abstract) **Commands**!
- Handler/Trigger of of provided **ConcreteCommands**


**ConcreteCommand (implementation):**

- Implements **Command** (its *execute()*-method)
- Connection between **Invoker** and **Receiver**
- One **ConcreteCommand** per **Receiver**-method()!


#### UML

```plantuml
hide circle
skinparam classAttributeIconSize 0
skinparam linetype ortho

title Command Pattern
    class Receiver {
        + action(): void
    }
    class Invoker <<interface>> {
        - Command Commands[0..*]
        + set(Command): void
        + handleCommands(): void
    }

    class Command <<abstract>> {
        + execute() void
    }
    Invoker o- Command

    class ConcreteCommand <<implementation>> {
        - Receiver receiver
        + Constructor(Receiver)
        + execute() void
    }
    Command <|-- ConcreteCommand
    Receiver <. ConcreteCommand

    note bottom
        execute() {
            doSomething()
        }
    endnote
```

### Null Object Pattern
(Code shown in combination with **Command** as *NullCommand*)


#### Description

- Used in combination with **other patterns**
- Used to have an object **NOT doing anything** 
- Used **like a regular operation** without having to change something else


#### Explanation


**Operation (abstract):**

- Interface for concrete **Operation**
- Decouples concrete **Operations** from the caller


**RealOperation (implementation):**

- Implements **Operation** (its *execute()*-method)
- Does something


**NullOperation (implementation):**

- Implements **Operation** (its *execute()*-method)
- Does **nothing**


#### UML

```plantuml
hide circle
skinparam classAttributeIconSize 0
skinparam linetype ortho

title Null Object Pattern

    class Operation <<abstract>> {
        + execute() void
    }

    class RealOperation <<implementation>> {
        + execute() void
    }
    Operation <|-- RealOperation
    note bottom
        execute() {
            doSomething()
        }
    endnote

    class NullOperation <<implementation>> {
        + execute() void
    }
    Operation <|-- NullOperation

    note bottom
        execute() {
            doSomething()
        }
    endnote
```