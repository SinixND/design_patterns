- [Design Patterns](#design-patterns)
  - [Creational Patterns](#creational-patterns)
    - [Singleton Pattern](#singleton-pattern)
      - [Description](#description)
      - [Explanation](#explanation)
      - [UML](#uml)
  - [Behavioral Patterns](#behavioral-patterns)
    - [Command Pattern](#command-pattern)
      - [Description](#description-1)
      - [Explanation](#explanation-1)
      - [UML](#uml-1)
    - [Null Object Pattern](#null-object-pattern)
      - [Description](#description-2)
      - [Explanation](#explanation-2)
      - [UML](#uml-2)
    - [TEMPLATE Pattern](#template-pattern)
      - [Description](#description-3)
      - [Explanation](#explanation-3)
      - [UML](#uml-3)


# Design Patterns


## Creational Patterns


### Singleton Pattern


#### Description

- Used to ensure that **only one instance** of a singleton exists at a time
- Used to provide a (controlled) **global access** to the object


#### Explanation


**Singleton:**

- Make **constructor private** to prevent unwanted instantiations (-> Rule of three!)
- Make an alternative (onstructor-like) function that creates an instance of (saved in (static) member) **only if** there is none yet


#### UML

```plantuml
hide circle
skinparam classAttributeIconSize 0
skinparam linetype ortho

title Singleton Pattern

    class Singleton {
        - Singleton instance
        - Constructor()
        + getInstance(): Singleton*
    }
    Singleton <|-- Singleton
```


## Behavioral Patterns


### Command Pattern


#### Description

- Used to make the connection (**Command** / request / order / call) from a trigger (**Invoker**) to an *executable action* (**Receiver**) a *manageable object*.

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
    - Examplary name: make*ReceiverMethod*
    - Examplary name: *methodReceiver*


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


### TEMPLATE Pattern


#### Description

- Used ...


#### Explanation


**TEMPLATECLASSELEMENT:**

- EXPLANATION


#### UML

```plantuml
hide circle
skinparam classAttributeIconSize 0
skinparam linetype ortho

title TEMPLATE Pattern

    class TEMPLATECLASSELEMENT <<abstract>> {
        + method() void
    }
    TEMPLATECLASSELEMENT <|-- TEMPLATECLASSELEMENT
```