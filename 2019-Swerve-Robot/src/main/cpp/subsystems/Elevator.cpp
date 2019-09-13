/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "Logger.h"

static const double maxPower = 0.1;
static const double minPower = -0.1;

void Elevator::setMode(OperationMode m) {
  mode = m;
}

Elevator::Elevator(int mainMotorId, int auxMotorId) :
  mainMotor(mainMotorId, rev::CANSparkMax::MotorType::kBrushless),
  auxMotor(auxMotorId, rev::CANSparkMax::MotorType::kBrushless),
  controller(mainMotor.GetPIDController()),
  Subsystem("ExampleSubsystem")
{
  auxMotor.Follow(mainMotor);
  auxMotor.SetInverted(true);

  mainMotor.RestoreFactoryDefaults();

  controller.SetP(0.01);
  controller.SetI(0.00);
  controller.SetD(0.00);
  controller.SetIZone(0.0);
  controller.SetFF(0.0);
  controller.SetOutputRange(minPower, maxPower);
}

void Elevator::setSetpoint(double point) {
  switch (mode) {
  case OperationMode::Disable:
    controller.SetOutputRange(0.0, 0.0);
    break;
  case OperationMode::Test:
    controller.SetOutputRange(-0.1, 0.1);
    break;
  case OperationMode::Enable:
    controller.SetOutputRange(minPower, maxPower);
    break;
  }
  logger::log("Set elevator setpoint to " + std::to_string(point), logger::Level::Info);
  controller.SetReference(point, rev::ControlType::kPosition);
}

void Elevator::InitDefaultCommand() {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
