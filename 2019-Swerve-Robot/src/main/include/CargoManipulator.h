/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DigitalInput.h>
#include <rev/SparkMax.h>
#include <ctre/Phoenix.h>
class CargoManipulator : public frc::Subsystem {
 private:
 rev::SparkMax neoMotor;
 WPI_VictorSPX otherMotor;
 frc::DigitalInput limitSwitch;

 public:
  CargoManipulator(int neoPort, int motorPort, int limitPort);
  void InitDefaultCommand() override;
  void setOutMotorSpeed(double speed);
  void extendManipulator(bool extend);
};
