/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>

#include <frc/PIDController.h>

class Elevator : public frc::Subsystem {
public:
  Elevator(int mainMotorId, int auxMotorId);
  void InitDefaultCommand() override;

private:
  void setSetpoint(double point);

  rev::CANSparkMax mainMotor, auxMotor;

  rev::CANPIDController controller;
};
