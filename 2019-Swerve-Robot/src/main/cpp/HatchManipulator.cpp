/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "HatchManipulator.h"

void HatchManipulator::setMode(OperationMode m) {
  mode = m;
}

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
  if (mode == OperationMode::Disable) {
    extendSolenoid.Set(false);
    retractSolenoid.Set(false);
  }
  else {
    extendSolenoid.Set(extended);
    retractSolenoid.Set(!extended);
  }
}

void HatchManipulator::setMotorSpeed(double speed) {
  double multiplier = 0.0;
  switch (mode) {
  case OperationMode::Disable:
    multiplier = 0.0;
    break;
  case OperationMode::Test:
    multiplier = 0.1;
    break;
  case OperationMode::Enable:
    multiplier = 1.0;
    break;
  }
  driveMotor.Set(speed * multiplier);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
