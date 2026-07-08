#include "VehicleState.h"

// Constructor
VehicleState::VehicleState(double curs, double tars, double acc)
    : current_speed(curs), target_speed(tars), acceleration(acc) {}

// Getters
double VehicleState::getCurrentSpeed() const {return current_speed;}
double VehicleState::getTargetSpeed()  const {return target_speed;}
double VehicleState::getAcceleration() const {return acceleration;}

// This is where the vehicle actually changes speed by applying acceleration to change speed
void VehicleState::updateState(double new_acceleration) {
    acceleration = new_acceleration;
    current_speed = current_speed + acceleration;

    // Bounds checking (e.g. speed can't go negative)
    if (current_speed < 0) {
        // What should I do here? PID overshot if we wound up here. Do I adjust PID on the fly?
    }
}

// Calculate how far off we are from the target
double VehicleState::getSpeedError() const {
    return target_speed - current_speed;
}