/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "HatchManipulator.h"

HatchManipulator::HatchManipulator(int extendPort, int retractPort, int motorPort) :
  Subsystem("HatchManipulator"),
  extendSolenoid(extendPort),
  retractSolenoid(retractPort),
  driveMotor(motorPort)
{
  setExtended(false);
  setMotorSpeed(0.0);
}

void HatchManipulator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  
}

void HatchManipulator::setExtended(bool extended) {
  extendSolenoid.Set(extended);
  retractSolenoid.Set(!extended);
}

void HatchManipulator::setMotorSpeed(double speed) {
  driveMotor.Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
