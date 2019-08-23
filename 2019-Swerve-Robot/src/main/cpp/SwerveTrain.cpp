/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SwerveTrain.h"
#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>

SwerveTrain::SwerveTrain(std::array< std::tuple< int, int, int, double >, moduleCount > &&m) :
  Subsystem("ExampleSubsystem")
{
  for (int i = 0; i < moduleCount; ++i) {
    modules[i] = std::make_unique< SwerveModule >(std::get<0>(m[i]), std::get<1>(m[i]), std::get<2>(m[i]), std::get<3>(m[i]));
  }
}

// Returns a magnitude/angle
std::pair< double, double > calcModuleTarget(double xSpeed, double ySpeed, double angSpeed, double robotAngle[3], int corner) {
  std::pair< double, double > target;

  target.first  = xSpeed * std::cos(-robotAngle[0] * M_PI / 180.0) - ySpeed * sin(-robotAngle[0] * M_PI / 180.0);
  target.second = xSpeed * std::sin(-robotAngle[0] * M_PI / 180.0) + ySpeed * cos(-robotAngle[0] * M_PI/ 180.0);
  
  target.first  += angSpeed * std::cos(((2 * corner) + 1) * M_PI_4);
  target.second += angSpeed * std::sin(((2 * corner) + 1) * M_PI_4);

  double mag = std::sqrt(target.first * target.first + target.second * target.second);
  double ang = std::atan2(target.second, target.first) * 360.0 / (2 * M_PI);

  target.first = mag;
  target.second = ang;

  return target;
}

void SwerveTrain::drive(double xSpeed, double ySpeed, double angSpeed) {
  double ypr[3];
  Robot::m_gyro->GetYawPitchRoll(ypr);

  ypr[0] -= 360.0 * std::floor(ypr[0] / 360.0);

  frc::SmartDashboard::PutNumber("Current Gyro", ypr[0]);

  static double targetGyro = 90.0;

  targetGyro -= 360.0 * std::floor(targetGyro / 360.0);

  targetGyro += angSpeed;

  frc::SmartDashboard::PutNumber("Target Gyro", targetGyro);

  double temp = (targetGyro - ypr[0] + 540.0);
  temp -= 360.0 * std::floor(temp / 360.0);
  temp -= 180.0;
  temp /= 32.0;

  //r += temp;

  frc::SmartDashboard::PutNumber("Turn amount", angSpeed);

  if (xSpeed * xSpeed + ySpeed * ySpeed + angSpeed * angSpeed >= 0.15) {
    // Rear right, front right, front left, rear left
    std::array< std::pair< double, double >, moduleCount > targets;

    double maxMag = -std::numeric_limits< double >::max();

    for (int i = 0; i < moduleCount; ++i) {
      auto target = calcModuleTarget(xSpeed, ySpeed, angSpeed, ypr, i);
      targets[i] = target;
      maxMag = std::max(maxMag, target.first);
    }

    // Scale vectors so none are greater than one
    if (maxMag > 1.0) {
      for (auto& vec : targets) {
        vec.first /= maxMag;
      }
    }

    for (int i = 0; i < 4; ++i) {
      frc::SmartDashboard::PutNumber("Swerve Target " + std::to_string(i), targets[i].second);
      modules[i]->Set(targets[i].first / 3.0, targets[i].second);
      //m_sparks[i]->Set(targets[i].first);
    }
  }
  else {
    for (int i = 0; i < 4; ++i) {
      modules[i]->Set(0.0, modules[i]->getAngle());
    }
  }

}

void SwerveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
