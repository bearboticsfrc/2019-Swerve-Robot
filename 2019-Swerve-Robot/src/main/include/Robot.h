/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <memory>
#include <array>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Joystick.h>

#include <rev/CANSparkMax.h>

#include "HatchManipulator.h"
#include "CargoManipulator.h"
#include "XboxControl.h"
#include "SwerveTrain.h"
#include "Elevator.h"

#include "commands/ManualDrive.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser< std::string > testModeChooser;

public:
  static std::unique_ptr< PigeonIMU > m_gyro;

  static std::unique_ptr< frc::Joystick > m_joystick;

  static std::unique_ptr< XboxControl > m_xboxController;

  /* ----- Subsystems ----- */
  static std::unique_ptr< SwerveTrain > swerveTrain;
  static std::unique_ptr< Elevator > elevator;
  static std::unique_ptr< HatchManipulator > hatchManipulator;
  static std::unique_ptr< CargoManipulator > cargoManipulator;

  /* ------ Commands ------ */
  static std::unique_ptr< ManualDrive > manualDrive;
};
