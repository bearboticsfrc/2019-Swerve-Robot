/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BallPlace.h"
#include "commands/DriveToTarget.h"
BallPlace::BallPlace() {
  
}

void BallPlace::Initialize() {}

void BallPlace::Execute() {
  DriveToTarget(true);
  //do the ball place thingy
}

bool BallPlace::IsFinished() { return false; }

// Called once after isFinished returns true
void BallPlace::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallPlace::Interrupted() {}
