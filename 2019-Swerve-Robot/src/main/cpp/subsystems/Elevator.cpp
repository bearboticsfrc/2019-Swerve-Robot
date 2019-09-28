/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "Logger.h"
#include <algorithm>

static const double maxPower = 0.2;
static const double minPower = -0.2;

void Elevator::setMode(OperationMode m) {
  mode = m;
  if (mode == OperationMode::Disable) {
    controller.Disable();
  }
  else {
    controller.Enable();
  }
}

double Elevator::getSensorPosition() {
  return mainMotor.GetEncoder().GetPosition();
}

Elevator::Elevator(int mainMotorId, int auxMotorId) :
  // TODO: FIX
  mainMotor(mainMotorId, rev::CANSparkMax::MotorType::kBrushless),
  auxMotor(auxMotorId, rev::CANSparkMax::MotorType::kBrushless),
  controller(0.2, 0.0002, 0.0, &neoPID, &mainMotor),
  Subsystem("ExampleSubsystem")
{
  auxMotor.Follow(mainMotor, true);
  //auxMotor.Follow(mainMotor);
  //auxMotor.SetInverted(false);
  //auxMotor.Disable();

  mainMotor.RestoreFactoryDefaults();

  controller.SetF(0.0);
  controller.SetPIDSourceType(frc::PIDSourceType::kDisplacement);
  controller.SetOutputRange(minPower, maxPower);
}

void Elevator::setSetpoint(double point) {
  if (point < 0.1) {
    point = 0.1;
  }
  if (point > 32.0) {
    point = 32.0;
  }
  switch (mode) {
  case OperationMode::Disable:
    controller.SetOutputRange(0.0, 0.0);
    break;
  case OperationMode::Test:
    controller.SetOutputRange(-0.2, 0.4);
    break;
  case OperationMode::Enable:
    controller.SetOutputRange(minPower, maxPower);
    break;
  }
  if (point != controller.GetSetpoint()) {
    logger::log("Set elevator setpoint to " + std::to_string(point), logger::Level::Info);
  }
  controller.SetSetpoint(point);
}

void Elevator::InitDefaultCommand() {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
