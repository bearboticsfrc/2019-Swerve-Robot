/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualElevator.h"
#include "XboxControl.h"
#include "Logger.h"
#include <unordered_map>
#include <Robot.h>

ManualElevator::ManualElevator() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ManualElevator::Initialize() {}

enum class Level {
  HatchLevel1,
  HatchLevel2,
  CargoLevel1,
  CargoLevel2,
  CargoLevel3,
  CargoShip,
};

std::unordered_map< Level, double > levelHeights{
  { Level::HatchLevel1, 0.595 },
  { Level::HatchLevel2, 21.524 },
  { Level::CargoLevel1, 0.0 },
  { Level::CargoLevel2, 16 },
  { Level::CargoLevel3, 32 },
  { Level::CargoShip, 0.1  }
};

Level levelFromInput(XboxControl& control) {
  if (control.controller.GetYButton()) {
    return Level::CargoLevel3;
  }
  if (control.controller.GetBButton()) {
    return Level::CargoLevel2;
  }
  if (control.controller.GetAButton()) {
    return Level::CargoLevel1;
  }
  if (control.controller.GetRawButton(8)) {
    return Level::CargoShip;
  }
  /*if (control.controller.GetPOV() == 0) {
    return Level::HatchLevel3;
  }*/
  if (control.controller.GetPOV() == 90) {
    return Level::HatchLevel2;
  }
  if (control.controller.GetPOV() == 180) {
    return Level::HatchLevel1;
  }
}

// Called repeatedly when this Command is scheduled to run
void ManualElevator::Execute() {
  auto level = levelFromInput(*Robot::m_xboxController);
  if (!levelHeights.count(level)) {
    logger::log("INVALID LEVEL " + std::to_string((int)level), logger::Level::Error);
  }
  else {
    Robot::elevator->setSetpoint(levelHeights.at(level));
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ManualElevator::IsFinished() { return false; }

// Called once after isFinished returns true
void ManualElevator::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualElevator::Interrupted() {}
