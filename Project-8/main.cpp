// Start the program

// // Create the physical robot arm
// Create a RobotArm object
//     - Set its starting position
//     - Tell it where the object is (pick location)
//     - Tell it where to drop the object (place location)

// // Create the brain / behavior
// Create a TaskController object
//     - Give it a reference to the RobotArm we just created

// Print a message like: "Starting pick and place simulation..."

// // Run the task for a number of steps
// For step from 1 to 60 (or until task is done):

//     // Let the state machine think and act for one time step
//     Call controller.step()

//     // Optional but very helpful for learning:
//     Print the current state of the TaskController
//     Print the current position of the RobotArm
//     Print whether it is holding the object or not

//     // Small pause so the output is readable (optional)

// // After the loop finishes
// Print a final message:
//     - Whether the task completed successfully (DONE state)
//     - Final position of the arm
//     - Whether it is still holding the object

// End the program