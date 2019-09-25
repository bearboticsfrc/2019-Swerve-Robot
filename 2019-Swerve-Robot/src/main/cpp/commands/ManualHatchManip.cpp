/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualHatchManip.h"
#include "Robot.h"

ManualHatchManip::ManualHatchManip() :
  frc::Command(*Robot::hatchManipulator)
{

}

// Called just before this Command runs the first time
void ManualHatchManip::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ManualHatchManip::Execute() {
  Robot::hatchManipulator->setExtended(Robot::m_joystick->GetTrigger());
  Robot::hatchManipulator->setSuction(Robot::m_joystick->GetZ() > 0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool ManualHatchManip::IsFinished() { return false; }

// Called once after isFinished returns true
void ManualHatchManip::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualHatchManip::Interrupted() {}
