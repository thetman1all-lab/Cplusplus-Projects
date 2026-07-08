#include "VehicleState.h"
#include "CruiseController.h"
#include <iostream>

int main() {
    // Start the program

    // Declare variables to be used
    double current_speed = 60.0;
    double target_speed = 70.0;
    double acceleration = 0.0;
    int step_tracker = 0;

    // Create a VehicleState object
    VehicleState VehSta(current_speed,target_speed,acceleration);

    // Create a CruiseController object
    // - Give it PID gains (kp, ki, kd)
    // - Give it max and min acceleration limits
    // * Start with reasonable PID gains in main.cpp (e.g. kp = 0.5, ki = 0.1, kd = 0.05) and adjust from there.
    CruiseController CruCon(1.0,1.0,1.0,3.0,-3.0);

    // Print a starting message (like "Starting cruise control simulation...")
    std::cout << "Starting cruise control simulation...\n";

    
    // Run a loop for 40 time steps
    for (int i = 0; i < 40; i++) {
        //     1. Ask the CruiseController: 
        //        "Based on current speed and target speed, what acceleration should I use?"
        acceleration = CruCon.computeControl(VehSta.getCurrentSpeed(), 70.0);

        //     2. Take that acceleration value and tell the VehicleState to update its speed
        VehSta.updateState(acceleration);

        //     3. (Optional but very helpful) Print the current speed and how far off we are from the target
        std::cout << "Current Speed: "           << VehSta.getCurrentSpeed() << " mph\n"
                  << "Error from Target Speed: " << VehSta.getSpeedError() << " mph\n";

        //     4. Wait a tiny bit (or just continue to the next step)

        // // Figure out how many steps it took to get to target speed
        // if (VehSta.getCurrentSpeed() == VehSta.getTargetSpeed()) {
        //     step_tracker = i;
        // } else {
        // }
        step_tracker++;
    }

    // Final vehicle report
    std::cout << "Final Speed: " << VehSta.getCurrentSpeed() << " mph\n"
              << "Final Speed Error: " << VehSta.getSpeedError() << " mph\n"
              << "Time Steps Taken: " << step_tracker << " steps\n";

    return 0;
}