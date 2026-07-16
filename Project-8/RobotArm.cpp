#include "RobotArm.h"

RobotArm::RobotArm(double initial_position, double pick_pos, double place_pos)
    : position(initial_position),
      holding_object(false),
      pick_position(pick_pos),
      place_position(place_pos)
{}

void RobotArm::moveToward(double target_position) {
    if (!isAtPosition(position)) {
        position += 1;
    }
}

bool RobotArm::grasp() {
    if (isAtPosition(position)) {
        return true;
    }
}

bool RobotArm::release() {
    if (position == place_position) {
        return true;
    }
}

double RobotArm::getPosition()      const {return position;}
bool   RobotArm::isHoldingObject()  const {return holding_object;}
double RobotArm::getPickPosition()  const {return pick_position;}
double RobotArm::getPlacePosition() const {return place_position;}

// Helper: Check if arm is close enough to a target
bool RobotArm::isAtPosition(double target, double tolerance = 1.0) const {
    if (target == position && std::abs(target - position) <= tolerance) {
        return true;
    }
}

// Optional: Print current state (useful for debugging)
void RobotArm::printStatus() const {
    std::cout << "Position: " << position
              << "Target: ";
}