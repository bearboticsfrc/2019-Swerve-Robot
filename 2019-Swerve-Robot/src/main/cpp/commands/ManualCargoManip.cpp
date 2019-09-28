/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualCargoManip.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "Robot.h"

ManualCargoManip::ManualCargoManip() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ManualCargoManip::Initialize() {
  Robot::cargoManipulator->extendManipulator(1);
}

enum class TakeMode {
  None, TryIntake, Outtake, Intake
};

std::string to_string(TakeMode mode) {
  const char *names[] = { "None", "TryIntake", "Outtake", "Intake" };
  return names[static_cast< int >(mode)];
}

// Called repeatedly when this Command is scheduled to run
void ManualCargoManip::Execute() {
  if (Robot::m_xboxController->controller.GetXButtonPressed()) {
      Robot::cargoManipulator->extendManipulator(1 + !Robot::cargoManipulator->getExtended());
  }

  static TakeMode takeMode = TakeMode::None;

  frc::SmartDashboard::PutString("Take Mode", to_string(takeMode));

  if (Robot::m_xboxController->controller.GetBumper(frc::GenericHID::JoystickHand::kRightHand)) {
    if (takeMode == TakeMode::None) {
      takeMode = TakeMode::TryIntake;
    }

    switch (takeMode) {
    case TakeMode::TryIntake:
      {
        static int successCount = 0;
        static int failCount = 0;
        if (Robot::cargoManipulator->getCurrent() > 4) {
          ++successCount;
        }
        else {
          ++failCount;
        }

        if (successCount > 20) {
          successCount = failCount = 0;
          takeMode = TakeMode::Outtake;
        }
        else if (failCount > 20) {
          successCount = failCount = 0;
          takeMode = TakeMode::Intake;
        }
      }
    case TakeMode::Intake:
      Robot::cargoManipulator->setIntakeSpeed(-1.0);
      break;
    case TakeMode::Outtake:
      Robot::cargoManipulator->setIntakeSpeed(1.0);
      break;
    }
  }
  else {
    Robot::cargoManipulator->setIntakeSpeed(0.0);
    takeMode = TakeMode::None;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ManualCargoManip::IsFinished() { return false; }

// Called once after isFinished returns true
void ManualCargoManip::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualCargoManip::Interrupted() {}
