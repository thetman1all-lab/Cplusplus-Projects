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
    double error;

public:
    // Constructor
    VehicleState(double curs, double tars, double acc);

    // Getters
    double getCurrentSpeed() const;
    double getTargetSpeed() const;
    double getAcceleration() const;


    // Applies acceleration to change speed
    void updateState(double new_acceleration);
    double getSpeedError() const;

    // Member function to print out data in clear format
    void print(std::ostream& out) const;
};

#endif