/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveTrain.h"
#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

void SwerveTrain::setMode(OperationMode m) {
  mode = m;
}

SwerveTrain::SwerveTrain(std::array< std::tuple< int, int, int, double >, moduleCount > m) :
  Subsystem("ExampleSubsystem")
{
  for (int i = 0; i < moduleCount; ++i) {
    modules[i] = std::make_unique< SwerveModule >(std::get<0>(m[i]), std::get<1>(m[i]), std::get<2>(m[i]), std::get<3>(m[i]));
  }
}

// Given a target robot speed in the x and y axis, and a target angular speed
// calculates the target magnitude and angle of the module with ID corner
std::pair< double, double > calcModuleTarget(double xSpeed, double ySpeed, double angSpeed, double robotAngle[3], int corner) {
  std::pair< double, double > target;

  target.first  = xSpeed * std::cos(-robotAngle[0] * M_PI / 180.0) - ySpeed * sin(-robotAngle[0] * M_PI / 180.0);
  target.second = xSpeed * std::sin(-robotAngle[0] * M_PI / 180.0) + ySpeed * cos(-robotAngle[0] * M_PI/ 180.0);
  
  // Direction of twist vector depends on which module is being used
  target.first  += angSpeed * std::cos(((2 * corner) + 1) * M_PI_4);
  target.second += angSpeed * std::sin(((2 * corner) + 1) * M_PI_4);

  double mag = std::sqrt(target.first * target.first + target.second * target.second);
  double ang = std::atan2(target.second, target.first) * 360.0 / (2 * M_PI);

  target.first = mag;
  target.second = ang;

  return target;
}

// Puts x in the interval [0, range)
double wrap(double x, double range) {
  double temp = std::fmod(x, range);
  return (temp < 0) ? range + x : x;
}

// Returns the signed difference a - b with the smallest magnitude
// e.g. will return -30 instead of 320
double angleDiff(double a, double b) {
  double temp = a - b + 180.0;
  wrap(temp, 360.0);
  return temp - 180.0;
}

void SwerveTrain::drive(double xSpeed, double ySpeed, double angSpeed) {
  double ypr[3];
  Robot::m_gyro->GetYawPitchRoll(ypr);

  ypr[0] = wrap(ypr[0], 360.0);

  frc::SmartDashboard::PutNumber("Current Gyro", ypr[0]);

  static double targetGyro = 90.0;

  targetGyro = wrap(targetGyro, 360.0);

  targetGyro += angSpeed;

  frc::SmartDashboard::PutNumber("Target Gyro", targetGyro);

  double temp = angleDiff(targetGyro, ypr[0]) / 32.0;

  //r += temp;

  frc::SmartDashboard::PutNumber("Turn amount", angSpeed);

  if (xSpeed * xSpeed + ySpeed * ySpeed + angSpeed * angSpeed >= 0.10 && mode != OperationMode::Disable) {
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
      double multiplier = ((mode == OperationMode::Test) ? 1.0 : 1.0);
      frc::SmartDashboard::PutNumber("Swerve Target " + std::to_string(i), targets[i].second);
      modules[i]->Set(targets[i].first * maxSpeed * multiplier, targets[i].second);
      //m_sparks[i]->Set(targets[i].first);
    }
  }
  else {
    for (int i = 0; i < 4; ++i) {
      modules[i]->Set(0.0, modules[i]->getAngle());
    }
  }

}

const SwerveModule &SwerveTrain::getModule(std::size_t idx) {
  return *modules[idx];
}

void SwerveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
