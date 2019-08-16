/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/phoenix/sensors/PigeonIMU.h>
#include "SwerveModule.h"
#include "XboxControl.h"
class SwerveTrain : public frc::Subsystem {
 private:
  static std::array< std::unique_ptr< SwerveModule >, 4 > m_swerveModules;
  static std::unique_ptr< PigeonIMU > m_gyro;

 public:
  SwerveTrain();
  void drive(double x, double y, double r);
  void init();
  void InitDefaultCommand() override;
};
