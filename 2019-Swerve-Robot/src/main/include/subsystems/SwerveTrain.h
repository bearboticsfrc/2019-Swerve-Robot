/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "SwerveModule.h"
#include "TestMode.h"

#include <frc/commands/Subsystem.h>
#include <tuple>
#include <array>

class SwerveTrain : public frc::Subsystem {
private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

public:
  static constexpr const std::size_t moduleCount = 4;
  static constexpr const double maxSpeed = 0.869; //nice
 
  void InitDefaultCommand() override;

  SwerveTrain(std::array< std::tuple< int, int, int, double >, moduleCount > m);

  void drive(double xSpeed, double ySpeed, double angSpeed);

  const SwerveModule &getModule(std::size_t idx);

  void setMode(OperationMode m);

  void doLogging();

private:
  OperationMode mode = OperationMode::Disable;

  std::array< std::unique_ptr< SwerveModule >, moduleCount > modules;
};
