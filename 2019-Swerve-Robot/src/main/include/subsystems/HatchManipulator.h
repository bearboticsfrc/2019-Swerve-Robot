/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "TestMode.h"

#include <frc/commands/Subsystem.h>
#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>

class HatchManipulator : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Solenoid extendSolenoid;
  frc::Solenoid retractSolenoid;

  frc::Solenoid suctionSolenoid;

  OperationMode mode = OperationMode::Disable;

 public:
  HatchManipulator(int extendPort, int retractPort, int suctionPort);
  void InitDefaultCommand() override;

  void setExtended(bool extended);

  void setSuction(bool suction);

  void setMode(OperationMode m);
};
