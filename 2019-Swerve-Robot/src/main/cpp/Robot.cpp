/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <math.h>
#include <frc/smartdashboard/SmartDashboard.h>

std::unique_ptr< SwerveTrain > Robot::m_swerveTrain{};
std::unique_ptr< HatchManipulator > Robot::hatchManipulator{};

std::unique_ptr< CargoManipulator > Robot::cargoManipulator{};
std::unique_ptr< XboxControl > m_xboxController{};
void Robot::RobotInit() {
  m_swerveTrain->init();
  //HatchManipulator(int extendPort, int retractPort, int motorPort);
  hatchManipulator = std::make_unique< HatchManipulator >(0, 1, 9);
  //CargoManipulator(int neoPort, int motorPort, int limitPort);
  cargoManipulator = std::make_unique< CargoManipulator >(10, 11, 2);

  frc::SmartDashboard::init();
}

void Robot::RobotPeriodic() {
}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  m_gyro->SetYaw(90.0);  }

void Robot::TeleopPeriodic() {
   //For Joystick control
  //double x =  m_joystick->GetX();
  //double y = -m_joystick->GetY();
  //double r = -m_joystick->GetZ();
  //For Xbox Control
  double x =  m_xboxController->GetLeftJoystickX();
  double y = -m_xboxController->GetLeftJoystickY();
  double r;
  if (m_xboxController->GetLeftBumper()) {
    r = -0.3;
  }
  else if (m_xboxController->GetRightBumper()) {
    r = 0.3;
  }
  else {
    r = 0; 
  }
  m_swerveTrain->drive(x, y, r);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
