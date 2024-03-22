// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShootCommands.h"

// Called when the command is initially scheduled.
void ShootCommands::Initialize() {
  // Start the shooter motors
  shooterSubsystem->SetShooterMotorVoltagePercent(shooter::kShooterMotorVoltagePercent);
  // Finished will always remain false, as this command is designed to be interrupted when complete
  timer.Reset();
  timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void ShootCommands::Execute() {
  // While the command is active, run the shooter motors
  shooterSubsystem->SetShooterMotorVoltagePercent(shooter::kShooterMotorVoltagePercent);
}

// Called once the command ends or is interrupted.
void ShootCommands::End(bool interrupted) {
  // Stop the shooter motors
  shooterSubsystem->StopShooter();
}

// Returns true when the command should end.
bool ShootCommands::IsFinished() {
  // Fallback if nothing else stops the command
  return timer.HasElapsed(4_s);
}
