#ifndef CRUISECONTROLLER_H
#define CRUISECONTROLLER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class CruiseController{
private:
    double kp;
    double ki;
    double kd;

    double integral;
    double previous_error;

    double max_acceleration;
    double min_acceleration;

    // 
    double calculateError(double current_speed, double target_speed) const;

    void updateIntegral(double error);

    double calculateDerivative(double error);

    double applyOutputLimits(double output) const;

public:
    // Constructor
    CruiseController(double p, double i, double d, double max_accel = 3.0, double min_accel = -3.0);

    // This is the main public interface. It should internally:
    // Calculate the error (target_speed - current_speed)
    // Update the integral term
    // Calculate the derivative term
    // Combine P + I + D terms
    // Clamp the final output between min_acceleration and max_acceleration
    // Store the current error for the next call (as previous_error)
    double computeControl(double current_speed, double target_speed) const;

    // Because the controller has state (integral and previous_error), it is good practice to reset them if needed
    void reset();
};

#endif