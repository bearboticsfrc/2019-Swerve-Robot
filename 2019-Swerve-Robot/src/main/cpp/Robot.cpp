/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

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
  testModeChooser.AddOption("Enable Mode", "enable");
  testModeChooser.AddOption("Test Mode", "test");
  testModeChooser.AddOption("Disable Mode", "disable");
  frc::SmartDashboard::PutData("Operation Mode Selector", &testModeChooser);

  testModeChooser.AddOption("Enable Mode", "enable");
  testModeChooser.AddOption("Test Mode", "test");
  testModeChooser.AddOption("Disable Mode", "disable");
  frc::SmartDashboard::PutData("Operation Mode Selector", &testModeChooser);

  // Swerve Module | Pivot Motor | Drive Motor
  // 1             | 5           | 0
  // 2             | 6           | 1
  // 3             | 7           | 2
  // 4             | 8           | 3

#define ENTRY(X) std::tuple< int, int, int, double >{ X + 1, X + 5, X, offsets[X] }

  // Initializes each swerve module based on the given ID and offset
  constexpr const std::array< double, SwerveTrain::moduleCount > offsets = { 28.0, 2.5, 27.0, 139.0 };
  swerveTrain = std::make_unique< SwerveTrain >(std::array< std::tuple< int, int, int, double >, SwerveTrain::moduleCount >{
    ENTRY(0),
    ENTRY(1),
    ENTRY(2),
    ENTRY(3)
  });

  m_joystick = std::make_unique< frc::Joystick >(0);
  m_xboxController = std::make_unique< XboxControl >(1);
  m_gyro = std::make_unique< PigeonIMU >(10);

  //HatchManipulator(int extendPort, int retractPort, int motorPort);
  //hatchManipulator = std::make_unique< HatchManipulator >(0, 1, 9);
  //CargoManipulator(int neoPort, int motorPort, int limitPort);
  //cargoManipulator = std::make_unique< CargoManipulator >(10, 11, 2);

  manualDrive = std::make_unique< ManualDrive >();

  swerveTrain->SetDefaultCommand(manualDrive.get());

  frc::SmartDashboard::init();
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

  if (!Robot::disableInput->Get()) {
    swerveTrain->setMode(OperationMode::Disable);
    elevator->setMode(OperationMode::Disable);
    hatchManipulator->setMode(OperationMode::Disable);
    cargoManipulator->setMode(OperationMode::Disable);
    return;
  }

  if (testModeChooser.GetSelected() == "enable") {
    std::cout << "Starting robot in ENABLEd mode\n";
    swerveTrain->setMode(OperationMode::Enable);
    elevator->setMode(OperationMode::Enable);
    hatchManipulator->setMode(OperationMode::Enable);
    cargoManipulator->setMode(OperationMode::Enable);
  }
  else if (testModeChooser.GetSelected() == "test") {
    std::cout << "Starting robot in TEST mode\n";
    swerveTrain->setMode(OperationMode::Test);
    elevator->setMode(OperationMode::Test);
    hatchManipulator->setMode(OperationMode::Test);
    cargoManipulator->setMode(OperationMode::Test);
  }
  else {
    if (testModeChooser.GetSelected() == "disable") {
      std::cout << "Starting robot in DISABLEd mode\n";
    }
    else {
      std::cout << "Invalid test option " << testModeChooser.GetSelected() << '\n';
    }
    swerveTrain->setMode(OperationMode::Disable);
    elevator->setMode(OperationMode::Disable);
    hatchManipulator->setMode(OperationMode::Disable);
    cargoManipulator->setMode(OperationMode::Disable);
  }
}

void Robot::TeleopPeriodic() {
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
