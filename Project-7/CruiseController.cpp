#include "CruiseController.h"
#include "VehicleState.h"

// * The integral and previous_error variables must be member variables (not local variables) because they need to persist between calls to computeControl().

// * Be careful with the sign of the error. In cruise control, we usually do target - current.

// * Start with reasonable PID gains in main.cpp (e.g. kp = 0.5, ki = 0.1, kd = 0.05) and adjust from there.

// Constructor
CruiseController::CruiseController(double p, double i, double d, double max_accel, double min_accel)
    : kp(p), ki(i), kd(d), max_acceleration(max_accel), min_acceleration(min_accel), integral(0), previous_error(0) {}
    // How do I properly initialize integral and previous_error to 0?

// Main control method - called every time step
double computeControl(double current_speed, double target_speed) {

    // Step 1: Calculate current error
    // error = calculateError(current_speed, target_speed)

    // Step 2: Update integral term (accumulated error over time)
    // updateIntegral(error)

    // // Step 3: Calculate derivative term (rate of change of error)
    // derivative = calculateDerivative(error)

    // // Step 4: Calculate raw PID output
    // output = (kp * error) + (ki * integral) + (kd * derivative)

    // // Step 5: Apply realistic limits to the output
    // limited_output = applyOutputLimits(output)

    // // Step 6: Store current error for next time step
    // previous_error = error

    // return limited_output;
}

// Helper: Calculate how far we are from target
double CruiseController::calculateError(double current_speed, double target_speed) const {
    return target_speed - current_speed;
}

// Helper: Accumulate error for integral term
void CruiseController::updateIntegral(double error) {
    integral = integral + error;
    // Optional: Add anti-windup logic here later if needed
}

// Helper: Calculate rate of change of error
double CruiseController::calculateDerivative(double error) {
    double derivative;
    derivative = error - previous_error;
    return derivative;
}

// Helper: Keep acceleration within realistic limits
double CruiseController::applyOutputLimits(double output) const{
    if (output > max_acceleration) {
        return max_acceleration;
    }
    else if (output < min_acceleration) {
        return min_acceleration;
    }
    else {
        return output;
    }
}

// Optional: Reset internal state (useful for testing)
void reset() {
    integral = 0;
    previous_error = 0;
}