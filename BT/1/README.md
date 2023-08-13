# Create Your Own ActionNodes with BehaviorTree.CPP

## What is an ActionNode?
In the context of Behavior Trees, an ActionNode represents a leaf node – a node that performs a specific action and then returns either SUCCESS, FAILURE, or RUNNING. The action can be anything: from moving a robot to a specific location, to playing a sound, or even just printing a message to the console.


## Creating a Custom ActionNode
The default (and recommended) way to create a TreeNode in BehaviorTree.CPP is by inheritance. Let's delve into the details:

### Define the Custom Node
Begin by defining a custom action node. In our example, we've created a node called SaySomething.

```c++
class SaySomething : public SyncActionNode
{
public:
    SaySomething(const std::string& name)
        : SyncActionNode(name, {})
    {
    }

    NodeStatus tick() override
    {
        std::string message = "Hello world";
        std::cout << "Robot says: " << message << std::endl;
        return NodeStatus::SUCCESS;
    }
};
```

Here's a breakdown:

* The custom node SaySomething inherits from SyncActionNode. This means it's a synchronous node that doesn't run in parallel with other nodes.
* The tick() function is overridden. This is the function that gets executed when the node runs. In this example, it simply prints a message to the console and returns a SUCCESS status.

### XML Representation of the Behavior Tree

For BehaviorTree.CPP, the structure of the tree can be defined using XML. Here's the XML representation of a simple tree that uses the SaySomething node:

```xml
<root main_tree_to_execute = "MainTree" >
 <BehaviorTree ID="MainTree">
  <Sequence name="root_sequence">
       <SaySomething name="simpleActionNode"/>
   </Sequence>
 </BehaviorTree>
</root>
```

This XML defines a tree with a single sequence node that contains our custom SaySomething action node.

### Execute the Behavior Tree
To execute the behavior tree, you need to:

* Create an instance of the BehaviorTreeFactory.
* Register the custom node type with the factory.
* Create a tree from the XML representation.
* Execute the tree using tree.tickWhileRunning().
* The main function in the provided code showcases these steps.