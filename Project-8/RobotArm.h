#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <iostream>

class RobotArm {
private:
    double position;              // Current position of the arm (abstract 1D for simplicity)
    bool holding_object;
    double pick_position;         // Where the object is located
    double place_position;        // Where to drop the object

public:
    // Constructor: Set initial position and the locations for pick/place
    RobotArm(double initial_position, double pick_pos, double place_pos);

    // Movement: Move toward a target position (simple step movement)
    void moveToward(double target_position);

    // Attempt to grasp the object at the current location
    bool grasp();

    // Release the object being held
    bool release();

    // Getters
    double getPosition() const;
    bool isHoldingObject() const;
    double getPickPosition() const;
    double getPlacePosition() const;

    // Helper: Check if arm is close enough to a target
    bool isAtPosition(double target, double tolerance = 1.0) const;

    // Optional: Print current state (useful for debugging)
    void printStatus() const;
};

#endif