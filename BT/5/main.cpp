#include "behaviortree_cpp/json_export.h"
#include "behaviortree_cpp/behavior_tree.h"
#include <behaviortree_cpp/bt_factory.h>

using namespace BT;

struct Pose2D
{
    double x, y, theta;
};

inline void to_json(nlohmann::json& dest, const Pose2D& pose) {
    dest["x"] = pose.x;
    dest["y"] = pose.y;
    dest["theta"] = pose.theta;
}

namespace BT
{
template <> inline
Pose2D convertFromString(StringView key)
{
    auto parts = BT::splitString(key, ';');
    if (parts.size() != 3)
    {
        throw BT::RuntimeError("invalid input)");
    }
    else
    {
        Pose2D output;
        output.x     = convertFromString<double>(parts[0]);
        output.y     = convertFromString<double>(parts[1]);
        output.theta = convertFromString<double>(parts[2]);
        return output;
    }
}
} // end namespace BT

class MoveToGoal : public BT::StatefulActionNode
{
public:
    MoveToGoal(const std::string& name, const BT::NodeConfig& config)
      : StatefulActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<Pose2D>("goal") };
    }

    BT::NodeStatus onStart() override;
    BT::NodeStatus onRunning() override;
    void onHalted() override;

private:
    Pose2D _goal;
    std::chrono::system_clock::time_point _completion_time;
};

BT::NodeStatus MoveToGoal::onStart()
{
    if (!getInput<Pose2D>("goal", _goal))
    {
        throw BT::RuntimeError("missing required input [goal]");
    }
    std::cout << "[ MoveToGoal: Moving robot towards the goal ]" << std::endl;
    _completion_time = std::chrono::system_clock::now() + std::chrono::milliseconds(220);
    return BT::NodeStatus::RUNNING;
}

BT::NodeStatus MoveToGoal::onRunning()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if(std::chrono::system_clock::now() >= _completion_time)
    {
        std::cout << "[ MoveToGoal: Reached the goal location ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    return BT::NodeStatus::RUNNING;
}

void MoveToGoal::onHalted()
{
    std::cout << "[ MoveToGoal: Navigation halted ]" << std::endl;
}

class CheckObstacle : public BT::SyncActionNode
{
public:
    CheckObstacle(const std::string& name) 
        : SyncActionNode(name, {})
    {}

    NodeStatus tick() override
    {
        std::cout << "Checking for obstacles..." << std::endl;
        // Here, we simulate that an obstacle is always detected for simplicity.
        // In real scenarios, sensor data would be used to detect obstacles.
        return BT::NodeStatus::FAILURE;
    }
};

class AnnounceObstacle : public BT::SyncActionNode
{
public:
    AnnounceObstacle(const std::string& name, const BT::NodeConfig& config)
        : SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("message") };
    }

    NodeStatus tick() override
    {
        Expected<std::string> msg = getInput<std::string>("message");
        if (!msg)
        {
            throw BT::RuntimeError("missing required input [message]: ", 
                                   msg.error() );
        }
        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

static const char* xml_text = R"(
<root>
    <BehaviorTree>
        <ReactiveSequence>
            <AnnounceObstacle message="Hello...."/>
            <Sequence>
                <MoveToGoal goal="10;10;0"/>
                <CheckObstacle/>
                <AnnounceObstacle message="Obstacle detected! Adjusting route."/>
            </Sequence>
        </ReactiveSequence>
    </BehaviorTree>
</root>
)";

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<MoveToGoal>("MoveToGoal");
    factory.registerNodeType<CheckObstacle>("CheckObstacle");
    factory.registerNodeType<AnnounceObstacle>("AnnounceObstacle");

    auto tree = factory.createTreeFromText(xml_text);
    NodeStatus status = tree.tickOnce();

    while(status == NodeStatus::RUNNING) 
    {
        std::cout << "--- ticking\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        status = tree.tickOnce();
        std::cout << "--- status: " << toStr(status) << "\n\n";
    }

    return 0;
}
