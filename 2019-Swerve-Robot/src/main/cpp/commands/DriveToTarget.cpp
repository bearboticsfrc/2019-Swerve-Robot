/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveToTarget.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "subsystems/SwerveTrain.h"
#include "Robot.h"
const static double camHeight = 0.0; //meters CHANGE
const static double ballHeight = 0.9937750000000002; // meters
const static double hatchHeight = 0.8; //meters
const static double camAngle = 0.0;
const static float kPDrive = 0.1;
static bool isCargo;
DriveToTarget::DriveToTarget(bool Cargo)
{
isCargo = Cargo;
}
double getBallDistance() {
  double distance = 0;
  float yAngle = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0);
  if (nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0) == 1) {
    //d = (h2-h1) / tan(a1+a2)
    distance = (ballHeight - camHeight) / tan(camAngle + yAngle);
  }
  return distance;
}
double getHatchDistance() {
  double distance = 0;
  float yAngle = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0);
  if (nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0) == 1) {
    //d = (h2-h1) / tan(a1+a2)
    double distance = (hatchHeight - camHeight) / tan(camAngle + yAngle) ;
  }
  return distance;
}
// Called just before this Command runs the first time
void DriveToTarget::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveToTarget::Execute() {
  if (isCargo) {
      double distance = getBallDistance();
      Robot::swerveTrain->drive(distance / kPDrive, 0.0, 0.0);
    }
  else {
    double distance = getHatchDistance();
    Robot::swerveTrain->drive(distance / kPDrive, 0.0, 0.0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToTarget::IsFinished() {
   return false; 
   }

// Called once after isFinished returns true
void DriveToTarget::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToTarget::Interrupted() {}
