/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "TestMode.h"

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>

#include <frc/PIDController.h>

class NeoPID : public frc::PIDSource {
public:
  NeoPID(rev::CANSparkMax *ptr) : spark(ptr) {}

  virtual double PIDGet() override {
    switch (m_pidSource) {
      case frc::PIDSourceType::kDisplacement:
        return spark->GetEncoder().GetPosition();
      case frc::PIDSourceType::kRate:
        return spark->GetEncoder().GetVelocity();
    }
  }

private:
  rev::CANSparkMax *spark;

};

class Elevator : public frc::Subsystem {
  friend class Robot;
public:
  Elevator(int mainMotorId, int auxMotorId);
  void InitDefaultCommand() override;

  void setMode(OperationMode m);

  double getSensorPosition();

  void setSetpoint(double point);

private:
  rev::CANSparkMax mainMotor, auxMotor;

  frc::PIDController controller;

  NeoPID neoPID{ &mainMotor };

  OperationMode mode = OperationMode::Disable;
};
