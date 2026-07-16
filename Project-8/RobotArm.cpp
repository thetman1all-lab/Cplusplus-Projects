#include "RobotArm.h"

RobotArm::RobotArm(double initial_position, double pick_pos, double place_pos)
    : position(initial_position),
      holding_object(false),
      pick_position(pick_pos),
      place_position(place_pos)
{}

void RobotArm::moveToward(double target_position) {
    if (isAtPosition(target_position)) {
        return; // Already there
    }
    // Move 1 unit toward the target
    if (position < target_position) {
        position += 1.0;
    } else {
        position -= 1.0;
    }
}

bool RobotArm::grasp() {
    // Can only grasp if we are close to the pick location and not already holding something
    if (isAtPosition(pick_position) && !holding_object) {
        holding_object = true;
        return true;
    }
    return false;
}

bool RobotArm::release() {
    if (isAtPosition(place_position) && holding_object) {
        holding_object = false;
        return true;
    }
    return false;
}

double RobotArm::getPosition()      const {return position;}
bool   RobotArm::isHoldingObject()  const {return holding_object;}
double RobotArm::getPickPosition()  const {return pick_position;}
double RobotArm::getPlacePosition() const {return place_position;}

// Helper: Check if arm is close enough to a target
bool RobotArm::isAtPosition(double target, double tolerance) const {
    if (target == position && std::abs(target - position) <= tolerance) {
        return true;
    }
    return false;
}

void RobotArm::printStatus() const {
    std::cout << "Position: " << position << "\n"
              << "Holding object: " << (holding_object ? "Yes" : "No") << "\n"
              << "Pick location: " << pick_position << "\n"
              << "Place location: " << place_position << "\n\n";
}