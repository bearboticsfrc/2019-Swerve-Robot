/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SafeManipulator.h"
#include "Robot.h"

SafeManipulator::SafeManipulator() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::cargoManipulator.get());
  Requires(Robot::hatchManipulator.get());
  Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void SafeManipulator::Initialize() {}

bool shouldInvertCargoManip() {
  return Robot::m_xboxController->controller.GetXButtonPressed();
}

// Called repeatedly when this Command is scheduled to run
void SafeManipulator::Execute() {
  switch (state) {
  case ManipState::Extended: {
    
  }
  case ManipState::Low: {
    if (Robot::elevator->isBlocked()) {
      Robot::cargoManipulator->setPosition(CargoManipulator::Position::PartialRetract);
      state = ManipState::Blocked;
      break;
    }
  }
  case ManipState::Blocked: {
    if (!Robot::elevator->isBlocked()) {
      Robot::cargoManipulator->setPosition(CargoManipulator::Position::FullRetract);
      state = (Robot::elevator->isLow() ? ManipState::Low : ManipState::High);
      break;
    }
  }
  case ManipState::High: {
    if (Robot::elevator->isBlocked()) {
      Robot::cargoManipulator->setPosition(CargoManipulator::Position::PartialRetract);
      state = ManipState::Blocked;
      break;
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool SafeManipulator::IsFinished() { return false; }

// Called once after isFinished returns true
void SafeManipulator::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SafeManipulator::Interrupted() {}
