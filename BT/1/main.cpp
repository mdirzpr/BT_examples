// Include the necessary headers for BehaviorTree.CPP
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/behavior_tree.h>

using namespace BT;

// Define a custom action node called SaySomething, which inherits from SyncActionNode
class SaySomething : public SyncActionNode
{
public:
    // Constructor that initializes the name and configuration of the node
    SaySomething(const std::string& name)
        : SyncActionNode(name, {})
    {
    }

    // Override the tick() method to specify the behavior of this node when it's executed
    NodeStatus tick() override
    {
        std::string message = "Hello world";

        // Print the message to the console
        std::cout << "Robot says: " << message << std::endl;
        // Return success status, indicating the node has successfully completed its task
        return NodeStatus::SUCCESS;
    }
};

// Define an XML representation of a behavior tree that uses the SaySomething node
static const char* xml_text = R"(
 <root main_tree_to_execute = "MainTree" >
  <BehaviorTree ID="MainTree">
   <Sequence name="root_sequence">
        <SaySomething name="simpleActionNode"/>
    </Sequence>
  </BehaviorTree>
</root>
)";

int main()
{
    // Create an instance of the BehaviorTreeFactory
    BehaviorTreeFactory factory;
    // Register the SaySomething node type with the factory
    factory.registerNodeType<SaySomething>("SaySomething");

    // Create a behavior tree from the XML representation
    auto tree = factory.createTreeFromText(xml_text);

    // Execute the behavior tree. This will run the SaySomething node and print the message
    tree.tickWhileRunning();

    // Return 0 to indicate successful execution of the program
    return 0;
}
