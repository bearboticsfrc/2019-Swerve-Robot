/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Elevator.h"

static const double maxPower = 0.1;
static const double minPower = -0.1;

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
  controller.SetReference(point, rev::ControlType::kPosition);
}

void Elevator::InitDefaultCommand() {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
