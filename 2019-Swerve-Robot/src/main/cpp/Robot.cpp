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
#include <cameraserver/CameraServer.h>
#include <frc/commands/Scheduler.h>
#include <frc/PowerDistributionPanel.h>

std::unique_ptr< frc::Joystick > Robot::m_joystick{};
std::unique_ptr< XboxControl > Robot::m_xboxController{};
std::unique_ptr< PigeonIMU > Robot::m_gyro{};
std::unique_ptr< frc::DigitalInput > Robot::disableInput{};

/* ----- Subsystems ----- */
std::unique_ptr< SwerveTrain > Robot::swerveTrain{};

/* ------ Commands ------ */
std::unique_ptr< ManualDrive > Robot::manualDrive{};

void Robot::RobotInit() {
  //frc::SmartDashboard::PutNumber("Operation Mode", 0);

  //vacuum = std::make_unique< WPI_VictorSPX >(ids::vacuum_port);

  testModeChooser.SetDefaultOption("Disable Mode", 0);
  testModeChooser.AddOption("Test Mode", 1);
  testModeChooser.AddOption("Enable Mode", 2);
  frc::SmartDashboard::PutData("Operation Mode Selector", &testModeChooser);

  // Initializes each swerve module based on the given ID and offset
  swerveTrain = std::make_unique< SwerveTrain >(ids::swerve_train_ids);

  m_joystick = std::make_unique< frc::Joystick >(ids::joystick_port);
  m_xboxController = std::make_unique< XboxControl >(ids::controller_port);
  m_gyro = std::make_unique< PigeonIMU >(ids::gyro_port);

  manualDrive = std::make_unique< ManualDrive >();
 
  swerveTrain->SetDefaultCommand(manualDrive.get());

  disableInput = std::make_unique< frc::DigitalInput >(9);

  logger::setLevel(logger::Level::Warning);

  if (!swerveTrain) {
    logger::log("Swervetrain subsystem has not been initialized.", logger::Level::Warning);
  }
 
  frc::CameraServer::GetInstance()->StartAutomaticCapture().SetResolution(160, 120);
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


  m_gyro->SetYaw(90.0);

  #define SET_SUBSYSTEM_MODE(sys, mode) do { if (sys) { sys->setMode(mode); } } while (0)

  if (!Robot::disableInput->Get()) {
    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Disable);
    return;
  }

  int selected = testModeChooser.GetSelected();

  if (selected == 2) {
    logger::log("Starting robot in ENABLEd mode", logger::Level::Info);
    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Enable);
    
    manualDrive->Start();
  }
  else if (selected == 1) {
    logger::log("Starting robot in TEST mode", logger::Level::Info);
    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Test);
 
    manualDrive->Start();
  }
  else {
    if (selected == 0) {
      logger::log("Starting robot in DISABLEd mode", logger::Level::Info);
    }
    else {
      logger::log("Invalid test option " + testModeChooser.GetSelected(), logger::Level::Error);
    }

    SET_SUBSYSTEM_MODE(swerveTrain, OperationMode::Disable);
  }

  #undef SET_SUBSYSTEM_MODE
}

void Robot::TeleopPeriodic() {
  frc::Scheduler::GetInstance()->Run();

  //vacuum->Set(1.0);
  
  if (m_xboxController->controller.GetRawButtonPressed(7)) {
    m_gyro->SetYaw(90.0);
  }

  frc::PowerDistributionPanel pdp;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
