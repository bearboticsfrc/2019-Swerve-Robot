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
#include <frc/DigitalInput.h>

#include <ctre/Phoenix.h>

#include "subsystems/SwerveTrain.h"
#include "subsystems/Elevator.h"
#include "subsystems/HatchManipulator.h"
#include "subsystems/CargoManipulator.h"
#include "XboxControl.h"

#include "commands/ManualDrive.h"
#include "commands/ManualHatchManip.h"
#include "commands/ManualCargoManip.h"
#include "commands/ManualElevator.h"

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
  frc::SendableChooser< int > testModeChooser;

  std::unique_ptr< WPI_VictorSPX > vacuum;

public:

  static std::unique_ptr< PigeonIMU > m_gyro;

  static std::unique_ptr< frc::Joystick > m_joystick;

  static std::unique_ptr< XboxControl > m_xboxController;

  static std::unique_ptr< frc::DigitalInput > disableInput;


  /* ----- Subsystems ----- */
  static std::unique_ptr< SwerveTrain > swerveTrain;
  static std::unique_ptr< Elevator > elevator;
  static std::unique_ptr< HatchManipulator > hatchManipulator;
  static std::unique_ptr< CargoManipulator > cargoManipulator;

  /* ------ Commands ------ */
  static std::unique_ptr< ManualDrive > manualDrive;
  static std::unique_ptr< ManualHatchManip > manualHatchManip;
  static std::unique_ptr< ManualCargoManip > manualCargoManip;
  static std::unique_ptr< ManualElevator > manualElevator;
};
