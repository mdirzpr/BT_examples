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
// The tree contains a sequence node with three child nodes: Task1, Task2, and Task3.
static const char* xml_text = R"(
<root BTCPP_format="4" >
    <BehaviorTree ID="MainTree">
       <Sequence name="root_sequence">
           <Task1 name="task1" />
           <Task2 name="task2" />
           <Task3 name="task3" />
       </Sequence>
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
