// Include the necessary headers for BehaviorTree.CPP
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/behavior_tree.h>

using namespace BT;

// Define a synchronous action node (SyncActionNode) that has an input port.
class SaySomething : public SyncActionNode
{
public:
    // Constructor for the Node with ports
    SaySomething(const std::string& name, const NodeConfig& config)
        : SyncActionNode(name, config)
    { }

    // Define the ports (inputs/outputs) of the node
    static PortsList providedPorts()
    {
        // This action has a single input port named "message"
        return { InputPort<std::string>("message") };
    }

    // The tick() function gets executed when the node runs
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
        
        // Print the provided message
        std::cout << "Robot says: " << msg.value() << std::endl;
        return NodeStatus::SUCCESS;
    }
};

// Define a synchronous action node that thinks of a message and provides it as output.
class ThinkWhatToSay : public SyncActionNode
{
public:
    ThinkWhatToSay(const std::string& name, const NodeConfig& config)
        : SyncActionNode(name, config)
    { }

    // Define the ports (inputs/outputs) of the node
    static PortsList providedPorts()
    {
        // This action provides an output named "text"
        return { OutputPort<std::string>("text") };
    }

    // The tick() function gets executed when the node runs
    NodeStatus tick() override
    {
        // Set the output message for this action
        setOutput("text", "The answer is 42" );
        return NodeStatus::SUCCESS;
    }
};

// Define the behavior tree structure in XML format
static const char* xml_text = R"(
<root BTCPP_format="4" >
    <BehaviorTree ID="MainTree">
       <Sequence name="root_sequence">
           <SaySomething     message="hello" />
           <ThinkWhatToSay   text="{the_answer}"/>
           <SaySomething     message="{the_answer}" />
       </Sequence>
    </BehaviorTree>
</root>
)";

int main()
{  
    // Create an instance of the BehaviorTreeFactory
    BehaviorTreeFactory factory;

    // Register the custom nodes with the factory
    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    // Create a behavior tree from the XML definition
    auto tree = factory.createTreeFromText(xml_text);

    // Execute the behavior tree
    tree.tickWhileRunning();

    return 0;
}
