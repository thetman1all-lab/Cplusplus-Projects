void TaskController::step() {

    // First, check what state we are currently in
    switch (current_state) {

        case TaskState::IDLE:
            // We haven't started the task yet
            // For now, we can just start moving toward the object
            transitionTo(TaskState::MOVING_TO_PICK);
            break;

        case TaskState::MOVING_TO_PICK:
            // We are trying to get to the object
            // Tell the arm to move closer to the pick location
            arm.moveToward(arm.getPickPosition());

            // Check if we've arrived close enough
            if (arm.isAtPosition(arm.getPickPosition())) {
                // We are close enough → time to try grabbing the object
                transitionTo(TaskState::GRASPING);
            }
            break;

        case TaskState::GRASPING:
            // We are at the object and trying to pick it up
            bool success = arm.grasp();

            if (success) {
                // We successfully grabbed the object
                transitionTo(TaskState::MOVING_TO_PLACE);
            } else {
                // Something went wrong with grabbing
                transitionTo(TaskState::ERROR);
            }
            break;

        case TaskState::MOVING_TO_PLACE:
            // We have the object and now need to take it to the drop location
            arm.moveToward(arm.getPlacePosition());

            if (arm.isAtPosition(arm.getPlacePosition())) {
                // We arrived at the drop location
                transitionTo(TaskState::RELEASING);
            }
            break;

        case TaskState::RELEASING:
            // We are at the drop location and need to let go of the object
            bool released = arm.release();

            if (released) {
                transitionTo(TaskState::DONE);
            } else {
                transitionTo(TaskState::ERROR);
            }
            break;

        case TaskState::DONE:
            // Task is finished. We can stay here or do nothing.
            // For now, we just stay in DONE.
            break;

        case TaskState::ERROR:
            // Something went wrong. For now we just stay here.
            // In a real system we might try to recover or stop safely.
            break;
    }
}