#ifndef VEHICLESTATE_H
#define VEHICLESTATE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class VehicleState {
private:
    // Private members
    double current_speed;
    double target_speed;
    double acceleration;

public:
    // Constructor
    VehicleState(double curs, double tars, double acc);

    // Getters
    double getCurrentSpeed() const;
    double getTargetSpeed() const;
    double getAcceleration() const;

    // Applies acceleration to change speed
    void updateState(double new_acceleration);

    // 
    double getSpeedError() const;

};

#endif