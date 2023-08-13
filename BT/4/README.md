# What is the Fallback Node?
The Fallback node, sometimes also known as a Selector, is a control flow node in a Behavior Tree. Its main purpose is to try each child node in order, from left to right, until one succeeds. If a child node fails, the Fallback will simply try the next one. The process stops as soon as a child node returns SUCCESS.

## Diving into the Example
```c++
// Include the necessary headers for BehaviorTree.CPP
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/behavior_tree.h>

using namespace BT;

// Define the Task1 node, which is a synchronous action node.
class Task1 : public SyncActionNode
{
public:
    // Constructor initializes the node name.
    Task1(const std::string name) 
    : SyncActionNode(name, {})
    {}

    // The tick() function is called when the node is executed.
    NodeStatus tick() override
    {
        // Print the task name.
        std::cout << "Task1: " << this->name() << std::endl;
        // Indicate that the task completed successfully.
        return NodeStatus::SUCCESS;
    }
};

// Define the Task2 node, another synchronous action node.
class Task2 : public SyncActionNode
{
public:
    Task2(const std::string name) 
    : SyncActionNode(name, {})
    {}

    NodeStatus tick() override
    {
        std::cout << "Task2: " << this->name() << std::endl;
        // Indicate that the task failed.
        return NodeStatus::FAILURE;
    }
};

// Define the Task3 node, another synchronous action node.
class Task3 : public SyncActionNode
{
public:
    Task3(const std::string name) 
    : SyncActionNode(name, {})
    {}

    NodeStatus tick() override
    {
        std::cout << "Task3: " << this->name() << std::endl;
        // Indicate that the task failed.
        return NodeStatus::FAILURE;
    }
};

// Define the behavior tree structure in XML format.
// The tree contains a Fallback node with three child nodes: Task1, Task2, and Task3.
static const char* xml_text = R"(
<root BTCPP_format="4" >
    <BehaviorTree ID="MainTree">
       <Fallback name="root_sequence">
           <Task1 name="task1" />
           <Task2 name="task2" />
           <Task3 name="task3" />
       </Fallback>
    </BehaviorTree>
</root>
)";

int main()
{  
    // Create an instance of the BehaviorTreeFactory.
    BehaviorTreeFactory factory;

    // Register the custom nodes with the factory so they can be used in behavior trees.
    factory.registerNodeType<Task1>("Task1");
    factory.registerNodeType<Task2>("Task2");
    factory.registerNodeType<Task3>("Task3");

    // Create a behavior tree from the XML definition.
    auto tree = factory.createTreeFromText(xml_text);

    // Execute the behavior tree.
    tree.tickWhileRunning();

    return 0;
}
```

In the provided code, we have three tasks: Task1, Task2, and Task3. Each task is a custom Action Node:

* Task1 always returns SUCCESS.
* Task2 and Task3 always return FAILURE.

These tasks are then embedded in a Fallback node in our Behavior Tree:
```xml
<Fallback name="root_sequence">
    <Task1 name="task1" />
    <Task2 name="task2" />
    <Task3 name="task3" />
</Fallback>
```
Given this structure, what do you anticipate when the tree executes?

## Execution Flow
* Task1 runs and returns SUCCESS.
* Since Task1 succeeded, the Fallback node doesn't execute Task2 or Task3. It stops right after the first success.
The result? We'll only see the print output from Task1.

## The Power of Fallback
Fallback nodes are especially useful in scenarios where you have multiple strategies to achieve a goal, and you want to try them in a preferred order. For instance, in robotics, a robot might have multiple ways to reach a destination. It can first try the shortest path. If that's blocked, it can try an alternative route, and so on. The Fallback node elegantly captures this behavior.


