// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeEjectCommand.h"


// Called when the command is initially scheduled.
void IntakeEjectCommand::Initialize() {
  /* Start the intake motors in the reverse direction
     Set finished to false to allow multiple calls of this command
  */
  
  if (currentMode == kCurrentHigh) {
    intakeSubsystem->SetSpinMotorCurrent(kCurrentHigh);
  }

  timer.Reset();
  timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void IntakeEjectCommand::Execute() {
  if (!timeDelay || timer.HasElapsed(1.2_s)) {
    intakeSubsystem->SetSpinMotorVoltagePercent(intake::kIntakeSpinMotorEjectVoltagePercent);
  }
}

// Called once the command ends or is interrupted.
void IntakeEjectCommand::End(bool interrupted) {
  //Stop the intake motors
  intakeSubsystem->StopIntake();

  if (currentMode == kCurrentHigh) {
    intakeSubsystem->SetSpinMotorCurrent(kCurrentLow);
  }
}

// Returns true when the command should end.
bool IntakeEjectCommand::IsFinished() {
  return timeDelay ? timer.HasElapsed(3_s) : timer.HasElapsed(2_s);
}
