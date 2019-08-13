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

#include <frc/smartdashboard/SmartDashboard.h>

//std::array< std::unique_ptr< rev::CANSparkMax >, 4 > Robot::m_sparks{};

std::array< std::unique_ptr< SwerveModule >, 4 > Robot::m_swerveModules{};

std::unique_ptr< frc::Joystick > Robot::m_joystick{};

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
  std::array< double, 4 > offsets = { 138.0, 354.0, 203.0, 139.0 };
  for (int i = 0; i < m_swerveModules.size(); ++i) {
    m_swerveModules[i] = std::make_unique< SwerveModule >(i + 1, i + 5, i, offsets[i]);
  }

  m_joystick = std::make_unique< frc::Joystick >(0);

  m_gyro = std::make_unique< PigeonIMU >(10);
  //HatchManipulator(int extendPort, int retractPort, int motorPort);
  hatchManipulator = std::make_unique< HatchManipulator >(0, 1, 9);
  //CargoManipulator(int neoPort, int motorPort, int limitPort);
  cargoManipulator = std::make_unique< CargoManipulator >(10, 11, 2);

  frc::SmartDashboard::init();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  for (int i = 0; i < m_swerveModules.size(); ++i) {
    double lastAngle = frc::SmartDashboard::GetNumber("Swerve Angle " + std::to_string(i), m_swerveModules[i]->getAngle());
    frc::SmartDashboard::PutNumber("Swerve Raw Angle " + std::to_string(i), m_swerveModules[i]->getRawAngle());
    frc::SmartDashboard::PutNumber("Swerve Angle " + std::to_string(i), m_swerveModules[i]->getAngle());

    double temp = m_swerveModules[i]->getAngle() + 360.0 - lastAngle;
    temp -= 360.0 * std::floor(temp / 360.0);

    frc::SmartDashboard::PutNumber("Swerve Speed " + std::to_string(i), temp);
  }
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
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
  m_gyro->SetYaw(90.0);
}

void Robot::TeleopPeriodic() {
  double x =  m_joystick->GetX();
  double y = -m_joystick->GetY();
  double r = -m_joystick->GetZ();

  static double targetGyro = 90.0;

  targetGyro -= 360.0 * std::floor(targetGyro / 360.0);

  targetGyro += r;

  frc::SmartDashboard::PutNumber("Target Gyro", targetGyro);

  double ypr[3];
  m_gyro->GetYawPitchRoll(ypr);

  ypr[0] -= 360.0 * std::floor(ypr[0] / 360.0);

  frc::SmartDashboard::PutNumber("Current Gyro", ypr[0]);

  double temp = (targetGyro - ypr[0] + 540.0);
  temp -= 360.0 * std::floor(temp / 360.0);
  temp -= 180.0;
  temp /= 32.0;

  //r += temp;

  frc::SmartDashboard::PutNumber("Turn amount", r);

  if (x * x + y * y + r * r >= 0.15) {
    // Rear right, front right, front left, rear left
    std::array< std::pair< double, double >, 4 > targets;

    double maxMag = -std::numeric_limits< double >::max();

    for (int i = 0; i < 4; ++i) {
      targets[i].first  = x * std::cos(-ypr[0] * M_PI / 180.0) - y * sin(-ypr[0] * M_PI / 180.0);
      targets[i].second = x * std::sin(-ypr[0] * M_PI / 180.0) + y * cos(-ypr[0] * M_PI/ 180.0);
      
      targets[i].first  += r * std::cos(((2 * i) + 1) * M_PI_4);
      targets[i].second += r * std::sin(((2 * i) + 1) * M_PI_4);

      //std::cout << targets[i].first << ", " << targets[i].second << "\n";

      double mag = std::sqrt(targets[i].first * targets[i].first + targets[i].second * targets[i].second);
      double ang = std::atan2(targets[i].second, targets[i].first) * 360.0 / (2 * M_PI);

      targets[i].first = mag;
      targets[i].second = ang;
      
      maxMag = std::max(maxMag, mag);
    }

    // Scale vectors so none are greater than one
    if (maxMag > 1.0) {
      for (auto& vec : targets) {
        vec.first /= maxMag;
      }
    }

    for (int i = 0; i < 4; ++i) {
      frc::SmartDashboard::PutNumber("Swerve Target " + std::to_string(i), targets[i].second);
      m_swerveModules[i]->Set(targets[i].first / 3.0, targets[i].second);
      //m_sparks[i]->Set(targets[i].first);
    }
  }
  else {
    for (int i = 0; i < 4; ++i) {
      m_swerveModules[i]->Set(0.0, m_swerveModules[i]->getAngle());
    }
  }

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
