/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "XboxControl.h"

XboxControl::XboxControl(int port) : 
Subsystem("XboxControl"),
controller(port)
 {

 }

void XboxControl::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
double XboxControl::GetLeftJoystickX() {
 return controller.GetX(frc::GenericHID::JoystickHand::kLeftHand);
}
double XboxControl::GetLeftJoystickY() {
  return controller.GetY(frc::GenericHID::JoystickHand::kLeftHand);
}
double XboxControl::GetRightJoystickX(){
  return controller.GetX(frc::GenericHID::JoystickHand::kRightHand);
}
double XboxControl::GetRightJoystickY() {
  return controller.GetY(frc::GenericHID::JoystickHand::kRightHand);
}
bool XboxControl::GetLeftBumper() {
  return controller.GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand);
}
bool XboxControl::GetRightBumper() {
  return controller.GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
