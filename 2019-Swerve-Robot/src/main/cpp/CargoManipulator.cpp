/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CargoManipulator.h"

CargoManipulator::CargoManipulator(int neoID, int motorPort, int limitPort) :
  Subsystem("CargoManipulator"),
  neoMotor(neoID, rev::CANSparkMax::MotorType::kBrushless),
  otherMotor(motorPort),
  limitSwitch(limitPort)
  { 
     extendManipulator(false);
     setOutMotorSpeed(0.0);
  }

void CargoManipulator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void CargoManipulator::setOutMotorSpeed(double speed) {
  // whatevermotorisintaking.Set(speed);
}

void CargoManipulator::extendManipulator(bool extend) {
  //if extend is true
  //check if limit switch is pressed
  //if it is: Extend
  /// if extend is false
  // reverse motor until limit switch is pressed
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
