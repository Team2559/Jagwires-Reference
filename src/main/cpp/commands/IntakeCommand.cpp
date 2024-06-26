// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeCommand.h"
#include <frc/DataLogManager.h>
#include <frc/RobotController.h>
#include <frc/shuffleboard/BuiltInWidgets.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardLayout.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <frc/shuffleboard/SimpleWidget.h>
#include <frc/smartdashboard/SmartDashboard.h>

// Called when the command is initially scheduled.
void IntakeCommand::Initialize() {
  /* Start the intake motors.
    Set finished to false to allow multiple calls of this command.
  */
  intakeSubsystem->SetSpinMotorVoltagePercent(intake::kIntakeSpinMotorVoltagePercent);
  intakeSubsystem->SetSpinMotorCurrent(kCurrentLow); //ensure the intake is at the right setting
  
  finished = false;
  frc::SmartDashboard::PutBoolean("Intake", false);
}

// Called repeatedly when this Command is scheduled to run
void IntakeCommand::Execute() {
  /* Checks if the limitswitches have been activated.  If so sets finished to true and intake to stop.
    Need to add code for moving arm pack to home position. */
  if (intakeSubsystem->HasNote()){
    
    intakeSubsystem->StopIntake();
    frc::SmartDashboard::PutBoolean("Intake", true); //Main section for highlighting some has been 
    finished = true;

    ledHold = false;

  }
  /*
  else {
    ledSubsystem->NormalColor();
  }*/
  
}

// Called once the command ends or is interrupted.
void IntakeCommand::End(bool interrupted) {

}

// Returns true when the command should end.
bool IntakeCommand::IsFinished() {
  return finished;
}
