/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "Logger.h"
#include "IDs.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <math.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/commands/Scheduler.h>

std::unique_ptr< frc::Joystick > Robot::m_joystick{};
std::unique_ptr< XboxControl > Robot::m_xboxController{};
std::unique_ptr< PigeonIMU > Robot::m_gyro{};
std::unique_ptr< frc::DigitalInput > Robot::disableInput{};

/* ----- Subsystems ----- */
std::unique_ptr< SwerveTrain > Robot::swerveTrain{};
std::unique_ptr< Elevator > Robot::elevator{};
std::unique_ptr< HatchManipulator > Robot::hatchManipulator{};
std::unique_ptr< CargoManipulator > Robot::cargoManipulator{};

/* ------ Commands ------ */
std::unique_ptr< ManualDrive > Robot::manualDrive{};

void Robot::RobotInit() {
  frc::SmartDashboard::init(); 
  testModeChooser.AddOption("Enable Mode", "enable");
  testModeChooser.AddOption("Test Mode", "test");
  testModeChooser.SetDefaultOption("Disable Mode", "disable");
  frc::SmartDashboard::PutData("Operation Mode Selector", &testModeChooser);

  // Initializes each swerve module based on the given ID and offset
  swerveTrain = std::make_unique< SwerveTrain >(ids::swerve_train_ids);

  m_joystick = std::make_unique< frc::Joystick >(ids::joystick_port);
  m_xboxController = std::make_unique< XboxControl >(ids::controller_port);
  m_gyro = std::make_unique< PigeonIMU >(ids::gyro_port);

  //HatchManipulator(int extendPort, int retractPort, int motorPort);
  //hatchManipulator = std::make_unique< HatchManipulator >(0, 1, 9);
  //CargoManipulator(int neoPort, int motorPort, int limitPort);
  //cargoManipulator = std::make_unique< CargoManipulator >(10, 11, 2);

  manualDrive = std::make_unique< ManualDrive >();

  swerveTrain->SetDefaultCommand(manualDrive.get());

  disableInput = std::make_unique< frc::DigitalInput >(9);

  if (!swerveTrain) {
    logger::log("Swervetrain subsystem has not been initialized.", logger::Level::Warning);
  }
  if (!elevator) {
    logger::log("Elevator subsystem has not been initialized.", logger::Level::Warning);
  }
  if (!hatchManipulator) {
    logger::log("Hatch manipulator subsystem has not been initialized.", logger::Level::Warning);
  }
  if (!cargoManipulator) {
    logger::log("Cargo manipulator subsystem has not been initialized.", logger::Level::Warning);
  }
}

void Robot::RobotPeriodic() {
  // Prints diagnostic information for each swerve module
  for (int i = 0; i < SwerveTrain::moduleCount; ++i) {
    double lastAngle = frc::SmartDashboard::GetNumber("Swerve Angle " + std::to_string(i), swerveTrain->getModule(i).getAngle());
    frc::SmartDashboard::PutNumber("Swerve Raw Angle " + std::to_string(i), swerveTrain->getModule(i).getRawAngle());
    frc::SmartDashboard::PutNumber("Swerve Angle " + std::to_string(i), swerveTrain->getModule(i).getAngle());

    double temp = swerveTrain->getModule(i).getAngle() + 360.0 - lastAngle;
    temp -= 360.0 * std::floor(temp / 360.0);

    frc::SmartDashboard::PutNumber("Swerve Speed " + std::to_string(i), temp);
  }
}

void Robot::AutonomousInit() {
 Robot::TeleopInit();
}

void Robot::AutonomousPeriodic() {
 Robot::TeleopPeriodic();
}

void Robot::TeleopInit() {
  frc::Scheduler::GetInstance()->RemoveAll();

  std::cout << "Starting teleop init\n";

  m_gyro->SetYaw(90.0);

  #define SET_SUBSYSTEM_MODE(sys, mode) do { if (sys) { sys->setMode(mode); } } while (0)

  if (!Robot::disableInput->Get()) {
    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Disable);
    SET_SUBSYSTEM_MODE(elevator, OperationMode::Disable);
    SET_SUBSYSTEM_MODE(hatchManipulator, OperationMode::Disable);
    SET_SUBSYSTEM_MODE(cargoManipulator, OperationMode::Disable);
    return;
  }

  if (testModeChooser.GetSelected() == "enable") {
    logger::log("Starting robot in ENABLEd mode", logger::Level::Info);
    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Enable);
    SET_SUBSYSTEM_MODE(elevator, OperationMode::Enable);
    SET_SUBSYSTEM_MODE(hatchManipulator, OperationMode::Enable);
    SET_SUBSYSTEM_MODE(cargoManipulator, OperationMode::Enable);
    
    manualDrive->Start();
  }
  else if (testModeChooser.GetSelected() == "test") {
    logger::log("Starting robot in TEST mode", logger::Level::Info);
    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Test);
    SET_SUBSYSTEM_MODE(elevator, OperationMode::Test);
    SET_SUBSYSTEM_MODE(hatchManipulator, OperationMode::Test);
    SET_SUBSYSTEM_MODE(cargoManipulator, OperationMode::Test);

    manualDrive->Start();
  }
  else {
    if (testModeChooser.GetSelected() == "disable") {
      logger::log("Starting robot in DISABLEd mode", logger::Level::Info);
    }
    else {
      logger::log("Invalid test option " + testModeChooser.GetSelected(), logger::Level::Error);
    }

    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Disable);
    SET_SUBSYSTEM_MODE(elevator, OperationMode::Disable);
    SET_SUBSYSTEM_MODE(hatchManipulator, OperationMode::Disable);
    SET_SUBSYSTEM_MODE(cargoManipulator, OperationMode::Disable);
  }

  #undef SET_SUBSYSTEM_MODE
}

void Robot::TeleopPeriodic() {
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
