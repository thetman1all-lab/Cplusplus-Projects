#include "RobotArm.h"
#include "TaskController.h"
#include <chrono>
#include <thread>

int main(){

    // RobotArm roarm(0, 5, 10);

    // for (int i = 0; i < 12; i++ ) {
        
    //     roarm.printStatus(); // Print what the fuck is going on

    //     roarm.grasp(); // Grasp the damn thing? HAS TO BE CALLED IF YOU WANT ROBO TO GRASP THE FUCKING OBJECT!

    //     roarm.moveToward(roarm.getPickPosition()); // Gotta move yo ass sometime in this lifetime


// Start the program

// // Create the physical robot arm
// Create a RobotArm object
//     - Set its starting position
//     - Tell it where the object is (pick location)
//     - Tell it where to drop the object (place location)
RobotArm robot_arm(0, 5, -18);

// // Create the brain / behavior
// Create a TaskController object
//     - Give it a reference to the RobotArm we just created
TaskController controller(robot_arm);

// Print a message like: "Starting pick and place simulation..."
std::cout << "Buckle the hell up, we're moking a 1D robot arm. ALso, starting pick and place simulation\n\n";

// // Run the task for a number of steps
// For step from 1 to 60 (or until task is done):
while (controller.getCurrentState() != TaskState::DONE) {
    // Let the state machine think and act for one time step
    // Call controller.step()
    controller.step();


    //     // Optional but very helpful for learning:
    //     Print the current state of the TaskController
    //     Print the current position of the RobotArm
    //     Print whether it is holding the object or not
    robot_arm.printStatus();

    //     // Small pause so the output is readable (optional)
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

}

// // After the loop finishes
// Print a final message:
//     - Whether the task completed successfully (DONE state)
//     - Final position of the arm
//     - Whether it is still holding the object

// End the program
    return 0;
}