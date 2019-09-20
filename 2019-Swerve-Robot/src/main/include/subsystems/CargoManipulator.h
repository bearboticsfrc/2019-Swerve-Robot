/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "TestMode.h"

#include <frc/commands/Subsystem.h>
#include <frc/AnalogInput.h>
#include <frc/PIDController.h>
#include <ctre/Phoenix.h>

class CargoManipulator : public frc::Subsystem {
private:
  WPI_VictorSPX intakeMotor;
  WPI_VictorSPX angleMotor;

  frc::AnalogInput angleSensor;

  frc::PIDController angleController;

  OperationMode mode = OperationMode::Disable;

public:
  CargoManipulator(int intakeMotorPort, int angleMotorPort, int angleSensorPort);
  void InitDefaultCommand() override;

  void setMode(OperationMode m);

  // +1.0 is maximum speed outwards, -1.0 is maximum speed inwards
  void setIntakeSpeed(double speed);

  void extendManipulator(bool extend);
};
