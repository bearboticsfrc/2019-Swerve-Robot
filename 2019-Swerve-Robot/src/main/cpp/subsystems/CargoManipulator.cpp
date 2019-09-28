/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoManipulator.h"
#include "Logger.h"

#include <frc/PowerDistributionPanel.h>

// TODO: Determine actual values for all of these
constexpr const static std::pair< double, double > maxAngleSpeed{ -0.5, 0.5 };
constexpr const static std::pair< double, double > maxIntakeSpeed{ -1.0, 1.0 };

constexpr const static double testMultiplier = 0.5;

constexpr const static double extendedAngle = 2.35;
constexpr const static double playingAngle = 3.8;
constexpr const static double retractedAngle = 4.0;

double CargoManipulator::getCurrent() const {
  frc::PowerDistributionPanel pdp;
  return pdp.GetCurrent(currentPort);
}

double CargoManipulator::getSensorPosition() {
  return angleSensor.GetVoltage();
}

void CargoManipulator::setMode(OperationMode m) {
  mode = m;
  switch (mode) {
  case OperationMode::Disable:
    angleController.Disable();
    intakeMotor.Set(0.0);
    break;
  case OperationMode::Test:
    angleController.Enable();
    angleController.SetOutputRange(maxAngleSpeed.first * testMultiplier, maxAngleSpeed.second * testMultiplier);
    break;
  case OperationMode::Enable:
    angleController.Enable();
    angleController.SetOutputRange(maxAngleSpeed.first, maxAngleSpeed.second);
    break;
  }
}

CargoManipulator::CargoManipulator(int intakeMotorPort, int angleMotorPort, int angleSensorPort) :
  Subsystem("CargoManipulator"),
  intakeMotor(intakeMotorPort),
  angleMotor(angleMotorPort),
  angleSensor(angleSensorPort),
  currentPort(intakeMotorPort),
  angleController(1.0, 0.0, 0.0, angleSensor, angleMotor)
{ 
  angleMotor.SetNeutralMode(NeutralMode::Brake);
  angleMotor.SetInverted(true);
  extendManipulator(false);
  setMode(OperationMode::Disable);
  angleController.Disable();
  angleController.SetSetpoint(retractedAngle);
}

bool CargoManipulator::getExtended() const {
  return std::abs(angleController.GetSetpoint() - extendedAngle) < 0.01;
}

void CargoManipulator::InitDefaultCommand(){
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void CargoManipulator::setIntakeSpeed(double speed) {
  std::array< double, 3 > multipliers{ 0.0, 0.4, 1.0 };

  intakeMotor.Set(speed * multipliers[static_cast< int >(mode)]);
}

void CargoManipulator::extendManipulator(int extend) {
    if (mode == OperationMode::Disable) {
      std::stringstream str;
      str << "Tried to set cargo manip extendedness to ";
      str << std::boolalpha << extend;
      str << "but it is disabled";
      logger::log(str.str(), logger::Level::Debug);
    }
    else {
      if (extend != getExtended()) {
        std::stringstream str;
        str << "Set cargo manipulator extendedness to ";
        str << std::boolalpha << extend;
        logger::log(str.str(), logger::Level::Info);
      }

      switch (extend) {
      case 0:
        angleController.SetSetpoint(retractedAngle);
        break;
      case 1:
        angleController.SetSetpoint(playingAngle);
        break;
      case 2:
        angleController.SetSetpoint(extendedAngle);
        break;
      case 3:
        angleController.SetSetpoint(3.6);
        break;
      }
    }
}
