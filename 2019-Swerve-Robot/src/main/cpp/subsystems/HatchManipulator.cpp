/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchManipulator.h"
#include "Logger.h"

void HatchManipulator::setMode(OperationMode m) {
  mode = m;
}

HatchManipulator::HatchManipulator(int extendPort, int retractPort, int suctionPort) :
  Subsystem("HatchManipulator"),
  extendSolenoid(extendPort),
  retractSolenoid(retractPort),
  suctionSolenoid(suctionPort)
{
  setExtended(false);
}

void HatchManipulator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  
}

void HatchManipulator::setExtended(bool extended) {
  if (mode == OperationMode::Disable) {
    logger::log("Tried to set hatch manipulator extendedness but disabled", logger::Level::Debug);
    extendSolenoid.Set(false);
    retractSolenoid.Set(false);
  }
  else {
    if (extended != extendSolenoid.Get()) {
      logger::log("Set hatch manipulator extendedness to " + std::to_string(extended), logger::Level::Info);
    }
    extendSolenoid.Set(!extended);
    retractSolenoid.Set(extended);
  }
}

bool HatchManipulator::getExtended() const {
  return !extendSolenoid.Get();
}

void HatchManipulator::setSuction(bool suction) {
  if (mode == OperationMode::Disable) {
    logger::log("Tried to set suction but disabled", logger::Level::Debug);
    suctionSolenoid.Set(false);
  }
  else {
    if (suction != suctionSolenoid.Get()) {
      logger::log("Set suction to " + std::to_string(suction), logger::Level::Info);
    }
      suctionSolenoid.Set(suction);
  }
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
