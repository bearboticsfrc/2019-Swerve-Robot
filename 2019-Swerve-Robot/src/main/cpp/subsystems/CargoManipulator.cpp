/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoManipulator.h"
#include "Logger.h"

// TODO: Determine actual values for all of these
constexpr const static std::pair< double, double > maxAngleSpeed{ -1.0, 1.0 };
constexpr const static std::pair< double, double > maxIntakeSpeed{ -1.0, 1.0 };

constexpr const static double testMultiplier = 0.1;

constexpr const static double extendedAngle = 0.0;
constexpr const static double retractedAngle = 0.1;

void CargoManipulator::setMode(OperationMode m) {
  mode = m;
  switch (mode) {
  case OperationMode::Disable:
    angleController.Disable();
    intakeMotor.Set(0.0);
    break;
  case OperationMode::Test:
    angleController.SetOutputRange(maxAngleSpeed.first * testMultiplier, maxAngleSpeed.second * testMultiplier);
    break;
  case OperationMode::Enable:
    angleController.SetOutputRange(maxAngleSpeed.first, maxAngleSpeed.second);
    break;
  }
}

CargoManipulator::CargoManipulator(int intakeMotorPort, int angleMotorPort, int angleSensorPort) :
  Subsystem("CargoManipulator"),
  intakeMotor(intakeMotorPort),
  angleMotor(angleMotorPort),
  angleSensor(angleSensorPort),
  angleController(0.1, 0.0, 0.0, angleSensor, angleMotor)
{ 
     extendManipulator(false);
     setMode(OperationMode::Disable);
}

void CargoManipulator::InitDefaultCommand(){
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void CargoManipulator::setIntakeSpeed(double speed) {
  std::array< double, 3 > multipliers{ 0.0, 0.1, 1.0 };

  intakeMotor.Set(speed * multipliers[static_cast< int >(mode)]);
}

void CargoManipulator::extendManipulator(bool extend) {
  if (mode == OperationMode::Disable) {
    std::stringstream str;
    str << "Tried to set cargo manip extendedness to ";
    str << std::boolalpha << extend;
    str << "but it is disabled";
    logger::log(str.str(), logger::Level::Debug);
  }
  else {
    std::stringstream str;
    str << "Set cargo manipulator extendedness to ";
    str << std::boolalpha << extend;
    logger::log(str.str(), logger::Level::Info);

    angleController.SetSetpoint(extend ? extendedAngle : retractedAngle);
  }
}
