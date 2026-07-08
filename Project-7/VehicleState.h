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
    VehicleState(double curs, double tars, double acc, double error);
    // FYI, error is just a placeholder that isn't really used except for data collection in main.cpp. This might be bad practice, but I'll figure out a better method later

    // Getters
    double getCurrentSpeed() const;
    double getTargetSpeed() const;
    double getAcceleration() const;
    double getSpeedError() const;

    // Applies acceleration to change speed
    void updateState(double new_acceleration);

    // Member function to print out data in clear format
    void print(std::ostream& out) const;
};

#endif