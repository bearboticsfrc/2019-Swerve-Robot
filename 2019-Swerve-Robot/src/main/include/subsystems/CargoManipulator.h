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
public:
  enum class Position {
    FullRetract, PartialRetract, Extend
  };

private:
  WPI_VictorSPX intakeMotor;
  WPI_VictorSPX angleMotor;

  int currentPort;

  frc::AnalogInput angleSensor;

  frc::PIDController angleController;

  OperationMode mode = OperationMode::Disable;

  Position position;

public:

  CargoManipulator(int intakeMotorPort, int angleMotorPort, int angleSensorPort);
  void InitDefaultCommand() override;

  double getSensorPosition();

  void setMode(OperationMode m);

  // +1.0 is maximum speed outwards, -1.0 is maximum speed inwards
  void setIntakeSpeed(double speed);

  void setPosition(Position pos);

  double getCurrent() const;

  Position getPosition() const;
};

std::ostream& operator<< (std::ostream& stream, CargoManipulator::Position pos);