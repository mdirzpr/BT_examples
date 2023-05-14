// main.cpp

#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/behavior_tree.h>

using namespace BT;

class SaySomething : public SyncActionNode
{
public:
    SaySomething(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return { InputPort<std::string>("message") };
    }

    NodeStatus tick() override
    {
        std::string message;
        getInput("message", message);
        std::cout << "Robot says: " << message << std::endl;
        return NodeStatus::SUCCESS;
    }
};

static const char* xml_text = R"(
<root>
  <BehaviorTree>
    <SaySomething message="Hello, World!" />
  </BehaviorTree>
</root>
)";

int main()
{
    BehaviorTreeFactory factory;
    factory.registerNodeType<SaySomething>("SaySomething");

    auto tree = factory.createTreeFromText(xml_text);

    tree.tickWhileRunning();

    return 0;
}