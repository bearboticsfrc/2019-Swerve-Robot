/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include "commands/ManualDrive.h"

ManualDrive::ManualDrive() :
  Command(*Robot::swerveTrain)
{

}

// Called just before this Command runs the first time
void ManualDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualDrive::Execute() {
  double x =  Robot::m_xboxController->GetLeftJoystickX();
  double y = -Robot::m_xboxController->GetLeftJoystickY();
  double r = -Robot::m_xboxController->GetRightJoystickX();

  x = x * x * x;
  y = y * y * y;

  r = r * r * r;
  r *= 0.5;

  Robot::swerveTrain->drive(x, y, r);
}

// Make this return true when this Command no longer needs to run execute()
bool ManualDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void ManualDrive::End() {
  Robot::swerveTrain->drive(0.0, 0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualDrive::Interrupted() {
  End();
}
