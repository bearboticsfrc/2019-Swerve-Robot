/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SwerveTrain.h"
#include <frc/smartdashboard/SmartDashboard.h>
SwerveTrain::SwerveTrain() : Subsystem("ExampleSubsystem") {
std::array< std::unique_ptr< SwerveModule >, 4 > SwerveTrain::m_swerveModules{};
std::unique_ptr< PigeonIMU > SwerveTrain::m_gyro{};

}

void SwerveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void SwerveTrain::init() {
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

  m_gyro = std::make_unique< PigeonIMU >(10);
}

void SwerveTrain::drive(double x, double y, double r) {
 
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
  for (int i = 0; i < m_swerveModules.size(); ++i) {
    double lastAngle = frc::SmartDashboard::GetNumber("Swerve Angle " + std::to_string(i), m_swerveModules[i]->getAngle());
    frc::SmartDashboard::PutNumber("Swerve Raw Angle " + std::to_string(i), m_swerveModules[i]->getRawAngle());
    frc::SmartDashboard::PutNumber("Swerve Angle " + std::to_string(i), m_swerveModules[i]->getAngle());

    double temp = m_swerveModules[i]->getAngle() + 360.0 - lastAngle;
    temp -= 360.0 * std::floor(temp / 360.0);

    frc::SmartDashboard::PutNumber("Swerve Speed " + std::to_string(i), temp);

}

