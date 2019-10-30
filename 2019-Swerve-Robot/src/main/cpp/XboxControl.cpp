/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "XboxControl.h"
#include <iostream>

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
  return controller.GetBumper(frc::GenericHID::JoystickHand::kLeftHand);
}
bool XboxControl::GetRightBumper() {
  return controller.GetBumper(frc::GenericHID::JoystickHand::kRightHand);
}
int XboxControl::GetDPadX() {
  int pov = controller.GetPOV();
  if (pov == -1) {
    return 0;
  }
  else if (45 <= pov && pov <= 135){
    return 1;
  }
  else if (225 <= pov && pov <= 315) {
    return -1;
  }
  else {
    return 0;
  }
}

int XboxControl::GetDPadY() {
  int pov = controller.GetPOV();
  if (pov == -1) {
    return 0;
  }
  else if (0 <= pov && pov <= 45) {
    return 1;
  }
  else if (315 <= pov) {
    return 1;
  }
  else if (135 <= pov && pov <= 225) {
    return -1;
  }
  else {
    return 0;
  }
}