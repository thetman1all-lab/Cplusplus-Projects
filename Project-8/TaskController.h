#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include "RobotArm.h"

enum class TaskState {
    IDLE,
    MOVING_TO_PICK,
    GRASPING,
    MOVING_TO_PLACE,
    RELEASING,
    DONE,
    ERROR
};

class TaskController {
private:
    RobotArm& arm;           // Reference to the robot arm (does NOT own it)
    TaskState current_state;

    // Helper methods for the state machine
    void transitionTo(TaskState new_state);
    bool checkConditionsForCurrentState();

public:
    // Constructor takes a reference to an existing RobotArm
    TaskController(RobotArm& robot_arm);

    // Main method called every simulation step
    void step();

    // Get current state (useful for printing/debugging)
    TaskState getCurrentState() const;

    // Optional: Reset the state machine
    void reset();
};

#endif