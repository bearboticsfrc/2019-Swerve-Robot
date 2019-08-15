/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../../test/main/cpp/XboxControl.h"

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
 return controller.GetX(kLeftHand);
}
double XboxControl::GetLeftJoystickY() {
  return controller.GetY(kLeftHand);
}
double XboxControl::GetRightJoystickX(){
  return controller.GetX(kRightHand);
}
double XboxControl::GetRightJoystickY() {
  return controller.GetY(kRightHand);
}
double XboxControl::
// Put methods for controlling this subsystem
// here. Call these from Commands.
