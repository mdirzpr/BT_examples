# Blackboards and Ports in BehaviorTree.CPP
In Behavior Trees (BT), data flow is essential. Whether you're building complex AI for a game or controlling a robot's movements, you often need nodes to communicate — passing information to one another. BehaviorTree.CPP offers a robust mechanism for this through the concepts of Blackboards and Ports. Let's dive into these features.

## Blackboards: The Shared Memory of BT
Imagine you're trying to remember a shopping list. You might jot it down on a board in your kitchen. In BT, the Blackboard serves a similar purpose. It's a shared memory space where nodes can store and retrieve information.

* What is a Blackboard?
A Blackboard is a key/value storage shared by all nodes of a tree. Every "entry" in the Blackboard is a pair, comprising a unique key and its associated value.

## Ports: The Gateways to the Blackboard
If the Blackboard is our kitchen board, then Ports are the pens we use to write on it or read from it. They allow nodes to interact with the Blackboard — either consuming data from it (input) or producing data to it (output).

* Input Ports: These are used by nodes to read data from the Blackboard. The data serves as the node's input parameters.

Here's an example of an Input Port in action:
```c++
class SaySomething : public SyncActionNode
{
public:
    // ... constructor and other parts ...

    static PortsList providedPorts()
    {
        // This action has a single input port named "message"
        return { InputPort<std::string>("message") };
    }

    NodeStatus tick() override
    {
        // Attempt to get the input named "message"
        Expected<std::string> msg = getInput<std::string>("message");
        
        // If the input isn't provided, throw an error
        if (!msg)
        {
            throw BT::RuntimeError("missing required input [message]: ", 
                                   msg.error() );
        }
        
        // Use the input
        std::cout << "Robot says: " << msg.value() << std::endl;
        return NodeStatus::SUCCESS;
    }
};
```

* Output Ports: These enable nodes to produce outputs that get stored in the Blackboard. Subsequent nodes can then use these outputs as their inputs.

Let's see an Output Port in action:
```c++
class ThinkWhatToSay : public SyncActionNode
{
public:
    // ... constructor and other parts ...

    static PortsList providedPorts()
    {
        // This action provides an output named "text"
        return { OutputPort<std::string>("text") };
    }

    NodeStatus tick() override
    {
        // Set the output message for this action
        setOutput("text", "The answer is 42" );
        return NodeStatus::SUCCESS;
    }
};
```

