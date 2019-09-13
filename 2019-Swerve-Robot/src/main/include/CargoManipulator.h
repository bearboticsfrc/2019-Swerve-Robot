/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "TestMode.h"

#include <frc/commands/Subsystem.h>
#include <frc/DigitalInput.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>

class CargoManipulator : public frc::Subsystem {
private:
  rev::CANSparkMax neoMotor;
  WPI_VictorSPX otherMotor;
  frc::DigitalInput limitSwitch;
  OperationMode mode = OperationMode::Disable;

public:
  CargoManipulator(int neoID, int motorPort, int limitPort);
  void InitDefaultCommand() override;
  void setOutMotorSpeed(double speed);
  void extendManipulator(bool extend);
  void setMode(OperationMode m);
};
