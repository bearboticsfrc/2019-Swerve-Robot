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

std::unique_ptr< SwerveTrain > Robot::swerveTrain{};

std::unique_ptr< frc::Joystick > Robot::m_joystick{};
std::unique_ptr< XboxControl > Robot::m_xboxController{};
std::unique_ptr< PigeonIMU > Robot::m_gyro{};

std::unique_ptr< HatchManipulator > Robot::hatchManipulator{};

std::unique_ptr< CargoManipulator > Robot::cargoManipulator{};

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  // Swerve Module | Pivot Motor | Drive Motor
  // 1             | 5           | 0
  // 2             | 6           | 1
  // 3             | 7           | 2
  // 4             | 8           | 3

#define ENTRY(X) std::tuple< int, int, int, double >{ X + 1, X + 5, X, offsets[X] }
  constexpr const std::array< double, SwerveTrain::moduleCount > offsets = { 138.0, 4.5, 203.0, 139.0 };
  swerveTrain = std::make_unique< SwerveTrain >(std::array< std::tuple< int, int, int, double >, SwerveTrain::moduleCount >{
    ENTRY(0),
    ENTRY(1),
    ENTRY(2),
    ENTRY(3)
  });

  m_joystick = std::make_unique< frc::Joystick >(0);
  m_xboxController = std::make_unique< XboxControl >(1);
  m_gyro = std::make_unique< PigeonIMU >(10);
  //HatchManipulator(int extendPort, int retractPort, int motorPort);
  //hatchManipulator = std::make_unique< HatchManipulator >(0, 1, 9);
  //CargoManipulator(int neoPort, int motorPort, int limitPort);
  //cargoManipulator = std::make_unique< CargoManipulator >(10, 11, 2);

  frc::SmartDashboard::init();

}

void Robot::RobotPeriodic() {
  for (int i = 0; i < SwerveTrain::moduleCount; ++i) {
    double lastAngle = frc::SmartDashboard::GetNumber("Swerve Angle " + std::to_string(i), swerveTrain->getModule(i).getAngle());
    frc::SmartDashboard::PutNumber("Swerve Raw Angle " + std::to_string(i), swerveTrain->getModule(i).getRawAngle());
    frc::SmartDashboard::PutNumber("Swerve Angle " + std::to_string(i), swerveTrain->getModule(i).getAngle());

    double temp = swerveTrain->getModule(i).getAngle() + 360.0 - lastAngle;
    temp -= 360.0 * std::floor(temp / 360.0);

    frc::SmartDashboard::PutNumber("Swerve Speed " + std::to_string(i), temp);
  }

}

void Robot::AutonomousInit() {
  /*
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
  */
 Robot::TeleopInit();
}

void Robot::AutonomousPeriodic() {
  /*
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
  */
 Robot::TeleopPeriodic();
}

void Robot::TeleopInit() {
  m_gyro->SetYaw(90.0);
  }

void Robot::TeleopPeriodic() {
  //For Joystick control
  //double x =  m_joystick->GetX();
  //double y = -m_joystick->GetY();
  //double r = -m_joystick->GetZ();
  //For Xbox Control
  double x = m_xboxController->GetLeftJoystickX();
  double y = -m_xboxController->GetLeftJoystickY();
  double r;
  if (m_xboxController->GetLeftBumper()) {
    r  = r + 0.1;
  }
  else if (m_xboxController->GetRightBumper()) {
    r = r - 0.1;
  }
  else {
    r = 0;
  }

  swerveTrain->drive(x, y, r);

  
  /* for (int i = 0; i < 4; ++i) {
    targets[i].second *= 360.0 / (2.0 * M_PI);
  }*/

  /*std::cout << std::setprecision(3);
  std::cout << std::setw(5) << targets[2].first << ",   " << std::setw(5) << targets[2].second
  << "     "  << std::setw(5) << targets[1].first << ",   " << std::setw(5) << targets[1].second << "\n\n";

  std::cout << std::setw(5) << targets[3].first << ",   " << std::setw(5) << targets[3].second
  << "     "  << std::setw(5) << targets[0].first << ",   " << std::setw(5) << targets[0].second << "\n\n\n" << std::endl;*/
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
