#include "VehicleState.h"

// Constructor
VehicleState::VehicleState(double curs, double tars, double acc, double err)
    : current_speed(curs),
      target_speed(tars),
      acceleration(acc),
      error(err)
{}

// Getters
double VehicleState::getCurrentSpeed() const {return current_speed;}
double VehicleState::getTargetSpeed()  const {return target_speed;}
double VehicleState::getAcceleration() const {return acceleration;}
double VehicleState::getSpeedError() const { return target_speed - current_speed;}

// This is where the vehicle actually changes speed by applying acceleration to change speed
void VehicleState::updateState(double new_acceleration) {
    acceleration = new_acceleration;
    current_speed = current_speed + acceleration;

    // Bounds checking (e.g. speed can't go negative)
    if (current_speed < 0) {
        // What should I do here? PID overshot if we wound up here. Do I adjust PID on the fly?
    }
}

 // Member function to print out data in clear format
void VehicleState::print(std::ostream& out) const {
    out << current_speed << "," << target_speed << "," << acceleration << "," << (target_speed - current_speed) << "\n";
}