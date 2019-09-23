/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchPlaceAuto.h"
#include "commands/DriveToTarget.h"
HatchPlaceAuto::HatchPlaceAuto() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void HatchPlaceAuto::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchPlaceAuto::Execute() {
  DriveToTarget(false);
  //Do the hatch place thingy
}

// Make this return true when this Command no longer needs to run execute()
bool HatchPlaceAuto::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchPlaceAuto::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchPlaceAuto::Interrupted() {}
