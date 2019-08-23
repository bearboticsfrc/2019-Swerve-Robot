/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignTarget.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

AlignTarget::AlignTarget() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::swerveTrain.get());
}

// Called just before this Command runs the first time
void AlignTarget::Initialize() {}

bool targetDetected() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);
}

double getXAngle() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
}

double getYAngle() {
    return nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0);
}

// Called repeatedly when this Command is scheduled to run
void AlignTarget::Execute() {
  double error = getXAngle();

  Robot::swerveTrain->drive(0.0, 0.0, error / 100.0);
}

// Make this return true when this Command no longer needs to run execute()
bool AlignTarget::IsFinished() { 
  return !targetDetected || std::abs(getXAngle()) < 1.0;
}

// Called once after isFinished returns true
void AlignTarget::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AlignTarget::Interrupted() {}
