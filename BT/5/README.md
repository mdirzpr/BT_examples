# Reactive and Asynchronous Behaviors
In the ever-evolving world of robotics, the ability to handle both reactive and asynchronous behaviors is crucial. This is especially true when robots navigate real-world environments filled with unpredictable variables. 

Imagine a robot tasked to move to a destination. This action isn't instantaneous; the robot might take several minutes to reach its goal, and during this journey, it could encounter unforeseen obstacles. This is inherently an asynchronous operation - the robot initiates the movement and continually checks its status until completion.

## Asynchronous Actions with StatefulActionNode:
In BTs, the StatefulActionNode is designed to handle asynchronous actions. It is particularly beneficial when you're dealing with a request-reply pattern. For instance, a robot sends a request to another system (like a map server) and periodically checks for a reply.

Key features of the StatefulActionNode are:

* onStart(): Triggered when the node transitions from the IDLE state. This could immediately return SUCCESS or FAILURE, or it might return RUNNING, indicating the action is still in progress. If RUNNING is returned, subsequent ticks will invoke onRunning().

* onRunning(): Invoked when the node is in the RUNNING state. This is where you'd typically check the status of your asynchronous operation and return either SUCCESS, FAILURE, or continue with RUNNING.

* onHalted(): Called when the action gets interrupted by another node in the tree. This is crucial for cleaning up resources or stopping ongoing operations safely.


## The Scenario:
Our robot's mission remains simple on the surface - navigate to a predetermined location. However, real-world challenges arise in the form of obstacles. Our robot needs to dynamically detect these barriers and react.

## Breaking Down the Behavior Tree:
1. MoveToGoal: An asynchronous node, representing the robot's movement towards its destination. Using the StatefulActionNode, the robot continually progresses towards its goal, checking for any interruptions or completion.

2. CheckObstacle: A synchronous node, simulating the robot's sensors to check for obstacles in its path. In real-life applications, this would integrate with sensors like LIDAR or cameras.

3. AnnounceObstacle: In the event of an obstacle detection, the robot announces its presence. This could be a simple log, a sound, or even a message sent to a control station.


## The Behavior Tree Structure:
Our BT starts with a ReactiveFallback node, ensuring that if one child node fails (like detecting an obstacle), the next child node is triggered.

Within this, we have a Sequence node. This ensures that the robot first moves towards its goal, checks for obstacles, and if one is found, announces it. The sequence ensures these actions are carried out in order.