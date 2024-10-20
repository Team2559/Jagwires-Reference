// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this pr
#include "Constants.h"
#include "RobotContainer.h"
#include "Robot.h"

#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/DriverStation.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/Command.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include "commands/IntakeCommand.h"
#include "commands/ClimberLowerCommand.h"
#include "commands/ClimberRaiseCommand.h"
#include "commands/ClimberStopCommand.h"
#include "commands/ShootCommands.h"
#include "commands/PIDTransferArmCommand.h"
#include "commands/IntakeEjectCommand.h"
#include "commands/DriveCommands.h"

#include <cmath>
#include <cstdio>
#include <functional>
#include <string>
#include <units/acceleration.h>
#include <units/velocity.h>
#include <frc2/command/button/RobotModeTriggers.h>

RobotContainer::RobotContainer() noexcept
{
  // Initialize all of your commands and subsystems here
  m_ledSubsystem.NormalColor();

  // Declaring the values used to set an autonomous mode
  m_autoChooser.SetDefaultOption(kAutoDefault, kAutoDefault);
  m_autoChooser.AddOption(kBlueLongAuto, kBlueLongAuto);
  m_autoChooser.AddOption(kBlueMiddleAuto, kBlueMiddleAuto);
  m_autoChooser.AddOption(kBlueShortAuto, kBlueShortAuto);
  m_autoChooser.AddOption(kRedShortAuto, kRedShortAuto);
  m_autoChooser.AddOption(kRedMiddleAuto, kRedMiddleAuto);
  m_autoChooser.AddOption(kRedLongAuto, kRedLongAuto);

  frc::SmartDashboard::PutData("Autonomous", &m_autoChooser);

  // Configure the button bindings
  ConfigureBindings();
  LEDStateBindings();
  ConfigureTransferArmBreak();
}

// #pragma region Autonomous
void RobotContainer::AutonomousInit() noexcept
{
  m_ledSubsystem.AllianceColor();

  m_driveSubsystem.ClearFaults();

  m_driveSubsystem.ResetEncoders();

  m_driveSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                      {&m_driveSubsystem}));
  m_intakeSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                       {&m_intakeSubsystem}));
  m_transferArmSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                       {&m_transferArmSubsystem}));
  m_shooterSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                        {&m_shooterSubsystem}));
  m_infrastructureSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                               {&m_infrastructureSubsystem}));



 
}

void RobotContainer::AutonomousPeriodic() noexcept {}

void RobotContainer::AutonomousExit() noexcept {}

std::optional<frc2::CommandPtr> RobotContainer::GetAutonomousCommand() noexcept
{
  // DriveCommand(xspeed, yspeed, rotation, time, &driveSubsystem)
  // will move in the given x and y direction while rotating for time seconds
  // xspeed, yspeed, and rotation will likely be between -1 and 1, but they do not need to be in these bounds
  // return ShootCommands(&m_shooterSubsystem).ToPtr().AlongWith(IntakeEjectCommand(&m_intakeSubsystem).ToPtr())
  // .AndThen(DriveCommand(0.0, 0.0, .3, 1.5_s, &m_driveSubsystem).ToPtr())
  // .AndThen(DriveCommand(0.7, 0.0, 0, 3_s, &m_driveSubsystem).ToPtr());

  std::string m_autoSelected = m_autoChooser.GetSelected();

  if (m_autoSelected == kBlueLongAuto)
  {
    return DriveCommand(.7, 0, 0, .8_s, &m_driveSubsystem).ToPtr()
    .AndThen(
      (
        frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */
        .AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentMed, &m_intakeSubsystem).ToPtr())
      ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
    )
    .AndThen(DriveCommand(.7, 0, 0, .7_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(0.0, 0, 0.5, .5_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(.7, 0.0, 0, 3_s, &m_driveSubsystem).ToPtr());
  }else if(m_autoSelected == kBlueMiddleAuto)
  {
    return DriveCommand(1.0, 0, 0, .85_s, &m_driveSubsystem).ToPtr()
    .AndThen(
      (
        frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */
        .AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentMed, &m_intakeSubsystem).ToPtr())
      ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
    )
    .AndThen(DriveCommand(0.7, 0, 0, 1_s, &m_driveSubsystem).ToPtr());
  }else if(m_autoSelected == kBlueShortAuto)
  {
    return DriveCommand(.7, 0, 0, .8_s, &m_driveSubsystem).ToPtr()
    .AndThen(
      (
        frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */
        .AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentMed, &m_intakeSubsystem).ToPtr())
      ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
    )
    .AndThen(DriveCommand(0.0, 0, -0.5, .7_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(0.7, 0, 0, 3_s, &m_driveSubsystem).ToPtr());
  }else if(m_autoSelected == kRedShortAuto)
  {
    return DriveCommand(.7, 0, 0, .8_s, &m_driveSubsystem).ToPtr()
    .AndThen(
      (
        frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */
        .AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentMed, &m_intakeSubsystem).ToPtr())
      ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
    )
    .AndThen(DriveCommand(0.0, 0, 0.5, .7_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(.7, 0.0, 0, 3_s, &m_driveSubsystem).ToPtr());
  }else if(m_autoSelected == kRedMiddleAuto)
  {
    return DriveCommand(1, 0, 0, .85_s, &m_driveSubsystem).ToPtr()
    .AndThen(
      (
        frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */
        .AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentMed, &m_intakeSubsystem).ToPtr())
      ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
    )
    .AndThen(DriveCommand(0.7, 0, 0, 1_s, &m_driveSubsystem).ToPtr());
  }else if(m_autoSelected == kRedLongAuto)
  {
    return DriveCommand(.7, 0, 0, .8_s, &m_driveSubsystem).ToPtr()
    .AndThen(
      (
        frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */
        .AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentMed, &m_intakeSubsystem).ToPtr())
      ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
    )
    .AndThen(DriveCommand(0.7, 0, 0, .7_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(0.0, 0, -0.5, .5_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(0.7, 0, 0, 3_s, &m_driveSubsystem).ToPtr());
  }else
  {
    return DriveCommand(1.0, 0, 0, .5_s, &m_driveSubsystem).ToPtr();
    // .AndThen(
    //   (
    //     frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */
    //     .AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentMed, &m_intakeSubsystem).ToPtr())
    //   ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
    // )
    // .AndThen(DriveCommand(0.7, 0, 0, 1.5_s, &m_driveSubsystem).ToPtr());
  }
       /*

  code below is used for alliance based operations
  used for relative from driver area:
  blue right of speaker
  red left of speaker
  
  std::optional<frc::DriverStation::Alliance> alliance = frc::DriverStation::GetAlliance(); 


  if (alliance == frc::DriverStation::Alliance::kRed)
  {
    return DriveCommand(.7, 0, 0, .5_s, &m_driveSubsystem).ToPtr()
    .AndThen(ShootCommands(&m_shooterSubsystem).ToPtr().AlongWith(IntakeEjectCommand(&m_intakeSubsystem).ToPtr()))
    .AndThen(DriveCommand(.7, 0, 0, .7_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(0.0, 0, 0.5, .5_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(.7, 0.0, 0, 3_s, &m_driveSubsystem).ToPtr());
  }
  else if (alliance == frc::DriverStation::Alliance::kBlue)
  {
    return DriveCommand(.7, 0, 0, .5_s, &m_driveSubsystem).ToPtr()
    .AndThen(ShootCommands(&m_shooterSubsystem).ToPtr().AlongWith(IntakeEjectCommand(&m_intakeSubsystem).ToPtr()))
    .AndThen(DriveCommand(.7, 0, 0, .7_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(0.0, 0, -0.5, .5_s, &m_driveSubsystem).ToPtr())
    .AndThen(DriveCommand(.7, 0.0, 0, 3_s, &m_driveSubsystem).ToPtr());
  }
  // Default (no alliance detected)
  return DriveCommand(.7, 0, 0, .5_s, &m_driveSubsystem).ToPtr()
  .AndThen(ShootCommands(&m_shooterSubsystem).ToPtr().AlongWith(IntakeEjectCommand(&m_intakeSubsystem).ToPtr()))
  .AndThen(DriveCommand(.7, 0, 0, .7_s, &m_driveSubsystem).ToPtr())
  .AndThen(DriveCommand(0.0, 0, 0.0, .5_s, &m_driveSubsystem).ToPtr())
  .AndThen(DriveCommand(0.0, 0.0, 0, 3_s, &m_driveSubsystem).ToPtr());
  */
}
// #pragma endregion

// #pragma region Teleop
void RobotContainer::TeleopInit() noexcept
{
  m_ledSubsystem.AllianceColor();

  m_driveSubsystem.ClearFaults();

  m_driveSubsystem.ResetEncoders();
  m_driveSubsystem.ZeroHeading();

  m_driveSubsystem.SetDefaultCommand(DriveCommandFactory(this));
  m_intakeSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                       {&m_intakeSubsystem}));
  m_shooterSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                        {&m_shooterSubsystem}));
  m_infrastructureSubsystem.SetDefaultCommand(frc2::RunCommand([&]() -> void {},
                                                               {&m_infrastructureSubsystem}));
}

void RobotContainer::TeleopPeriodic() noexcept {}

void RobotContainer::TeleopExit() noexcept {}

void RobotContainer::LEDStateBindings() noexcept {
  auto noteTrigger = frc2::Trigger([&]() -> bool {return m_intakeSubsystem.HasNote();});
  auto disabledTrigger = frc2::RobotModeTriggers::Disabled();

  auto normalLEDCommand = new frc2::InstantCommand([&]() -> void {m_ledSubsystem.NormalColor();});
  auto allianceLEDCommand = new frc2::InstantCommand([&]() -> void {m_ledSubsystem.AllianceColor();});
  auto noteLEDCommand = new frc2::InstantCommand([&]() -> void {m_ledSubsystem.NoteColor();});

  disabledTrigger.OnTrue(normalLEDCommand);
  (!disabledTrigger && !noteTrigger).OnTrue(allianceLEDCommand);
  (!disabledTrigger && noteTrigger).OnTrue(noteLEDCommand);
}

void RobotContainer::ConfigureTransferArmBreak() noexcept {
  auto disabledTrigger = frc2::RobotModeTriggers::Disabled();

  m_transferArmSubsystem.ReleaseBreak();
  disabledTrigger.OnTrue(new frc2::InstantCommand([&]() -> void {m_transferArmSubsystem.ReleaseBreak();}));
  disabledTrigger.OnFalse(new frc2::InstantCommand([&]() -> void {m_transferArmSubsystem.LockBreak();}));
}

frc2::CommandPtr RobotContainer::DriveCommandFactory(RobotContainer *container) noexcept
{
  // Set up default drive command; non-owning pointer is passed by value.
  auto driveRequirements = {dynamic_cast<frc2::Subsystem *>(&container->m_driveSubsystem)};

  // Drive, as commanded by operator joystick controls.
  return frc2::CommandPtr{std::make_unique<frc2::RunCommand>(
      [container]() -> void
      {
        if (container->m_lock)
        {
          (void)container->m_driveSubsystem.SetLockWheelsX();

          return;
        }

        const auto controls = container->GetDriveTeleopControls();

        container->m_driveSubsystem.Drive(
            std::get<0>(controls) * physical::kMaxDriveSpeed,
            std::get<1>(controls) * physical::kMaxDriveSpeed,
            std::get<2>(controls) * physical::kMaxTurnRate,
            std::get<3>(controls));
      },
      driveRequirements)};
}

std::tuple<double, double, double, bool> RobotContainer::GetDriveTeleopControls() noexcept
{
  /*
  The robot's frame of reference is the standard unit circle, from
  trigonometry.  However, the front of the robot is facing along the positve
  X axis.  This means the poitive Y axis extends outward from the left (or
  port) side of the robot.  Poitive rotation is counter-clockwise.  On the
  other hand, as the controller is held, the Y axis is aligned with forward.
  And, specifically, it is the negative Y axis which extends forward.  So,
  the robot's X is the controllers inverted Y.  On the controller, the X
  axis lines up with the robot's Y axis.  And, the controller's positive X
  extends to the right.  So, the robot's Y is the controller's inverted X.
  Finally, the other controller joystick is used for commanding rotation and
  things work out so that this is also an inverted X axis.
  */
  double LeftTrigAnalogVal = m_xboxDrive.GetLeftTriggerAxis();
  double LeftStickX = -m_xboxDrive.GetLeftY();
  double LeftStickY = -m_xboxDrive.GetLeftX();
  double rightStickRot = -m_xboxDrive.GetRightX();

  if (LeftTrigAnalogVal < .05)
  {
    LeftStickX *= physical::kSlowDrivePercent;
    LeftStickY *= physical::kSlowDrivePercent;
  }
  

  if (triggerSpeedEnabled) // scale speed by analog trigger
  {
    double RightTrigAnalogVal = m_xboxDrive.GetRightTriggerAxis();
    RightTrigAnalogVal = ConditionRawTriggerInput(RightTrigAnalogVal);

    if (LeftStickX != 0 || LeftStickY != 0)
    {
      if (LeftStickX != 0)
      {
        double LeftStickTheta = atan(LeftStickY / LeftStickX);
        LeftStickX = RightTrigAnalogVal * cos(LeftStickTheta);
        LeftStickY = RightTrigAnalogVal * sin(LeftStickTheta);
      }
      else
      {
        LeftStickY = std::copysign(RightTrigAnalogVal, LeftStickY);
      }
    }
  }
  else // scale speed by analog stick
  {
    LeftStickX = ConditionRawJoystickInput(LeftStickX);
    LeftStickY = ConditionRawJoystickInput(LeftStickY);
  }

  rightStickRot = ConditionRawJoystickInput(rightStickRot);

  return std::make_tuple(LeftStickX, LeftStickY, rightStickRot, m_fieldOriented);
}

double RobotContainer::ConditionRawTriggerInput(double RawTrigVal) noexcept
{
  // Set a raw trigger value using the right trigger
  RawTrigVal = m_xboxDrive.GetRightTriggerAxis();
  double deadZoneVal = 0.05;
  double deadZoneCorrection = 1.0 / (1.0 - deadZoneVal);

  if (RawTrigVal < deadZoneVal)
  {
    /*if the trigger value is less than deadzonevalue, it will
    set the right trigger value to zero to correct drifting*/
    return 0;
  }
  else
  {
    /* if the trigger value is greater than the deadzonevalue, it will
    make a small correction to stop the increase in speed from being
    too big */
    RawTrigVal -= deadZoneVal;
    RawTrigVal *= deadZoneCorrection;
    return std::pow(RawTrigVal, 3.0); // std::pow(RawTrigVal, 3.0) == RawTrigVal^3
  }
}

double RobotContainer::ConditionRawJoystickInput(double RawJoystickVal, double mixer) noexcept
{
  /*
  PlayStation controllers seem to do this strange thing with the rotation:
  double z = -m_xbox.GetLeftTriggerAxis();
  Note: there is now a PS4Controller class.

  Add some deadzone, so the robot doesn't drive when the joysticks are
  released and return to "zero".  These implement a continuous deadband, one
  in which the full range of outputs may be generated, once joysticks move
  outside the deadband.

  Also, cube the result, to provide more opertor control.  Just cubing the
  raw value does a pretty good job with the deadband, but doing both is easy
  and guarantees no movement in the deadband.  Cubing makes it easier to
  command smaller/slower movements, while still being able to command full
  power.  The 'mixer` parameter is used to shape the `raw` input, some mix
  between out = in^3.0 and out = in.
  */

  // Input deadband around 0.0 (+/- range).
  constexpr double deadZoneVal = 0.05;

  constexpr double slope = 1.0 / (1.0 - deadZoneVal);

  if (RawJoystickVal >= -deadZoneVal && RawJoystickVal <= +deadZoneVal)
  {
    RawJoystickVal = 0.0;
  }
  else if (RawJoystickVal < -deadZoneVal)
  {
    RawJoystickVal += deadZoneVal;
    RawJoystickVal *= slope;
  }
  else if (RawJoystickVal > +deadZoneVal)
  {
    RawJoystickVal -= deadZoneVal;
    RawJoystickVal *= slope;
  }

  return mixer * std::pow(RawJoystickVal, 3.0) + (1.0 - mixer) * RawJoystickVal;
}

void RobotContainer::ConfigureBindings() noexcept
{
  // TODO: define Keybindings here
  m_xboxDrive.Start().OnTrue(
      frc2::InstantCommand([&]() -> void
                           { triggerSpeedEnabled = !triggerSpeedEnabled; },
                           {})
          .ToPtr());

  m_xboxDrive.X().OnTrue(
          frc2::InstantCommand([&]() -> void
                           { m_driveSubsystem.ZeroHeading(); },
                           {})
          .ToPtr());

  m_xboxOperate.A().OnTrue(IntakeCommand(&m_intakeSubsystem).ToPtr());
  m_xboxOperate.B().OnTrue(IntakeEjectCommand(IntakeMotorCurrent::kCurrentHigh, &m_intakeSubsystem).ToPtr());

  // Runs shoot command to move arm into postion, start up the shooting motors and eject the note
  m_xboxOperate.Y().OnTrue(
    (
      (
        PIDPositionTransferArm(arm::kArmToShooterAngle, &m_transferArmSubsystem).ToPtr()
        .AlongWith(frc2::cmd::Wait(shooter::kShooterSpoolTime) /* Minimum time for shooter motors to spool */)
      ).AndThen(IntakeEjectCommand(IntakeMotorCurrent::kCurrentHigh, &m_intakeSubsystem).ToPtr())
    ).DeadlineWith(ShootCommands(&m_shooterSubsystem).ToPtr())
  );

  //X button for shooting in the amp
  m_xboxOperate.X().OnTrue(PIDPositionTransferArm(arm::kArmToAmpAngle, &m_transferArmSubsystem).ToPtr());
    // .AndThen(IntakeEjectCommand(intake::timerDelayAmp, IntakeMotorCurrent::kCurrentHigh, &m_intakeSubsystem).ToPtr()));

  m_xboxOperate.LeftBumper().OnTrue(PIDPositionTransferArm(arm::kArmToIntakeAngle, &m_transferArmSubsystem).ToPtr()); // Intake
  m_xboxOperate.RightBumper().OnTrue(PIDPositionTransferArm(arm::kArmToShooterAngle, &m_transferArmSubsystem).ToPtr()); // Shooter

  m_xboxOperate.RightTrigger().WhileTrue(ClimberRaiseCommand(&m_climberSubsystem).ToPtr()); // Raise the climber while button is pressed.
  // m_xboxOperate.RightTrigger().OnFalse(ClimberStopCommand(&m_climberSubsystem).ToPtr());   // on false stop the climber motor

  m_xboxOperate.LeftTrigger().WhileTrue(ClimberLowerCommand(&m_climberSubsystem).ToPtr()); //Lower the climber while button is pressed
  // m_xboxOperate.LeftTrigger().OnFalse(ClimberStopCommand(&m_climberSubsystem).ToPtr());   // on false stop the climber motor

  

  //Shooter start and stop

  dpadUp.OnTrue(frc2::InstantCommand([&]() -> void
          {m_shooterSubsystem.SetShooterMotorVoltagePercent(shooter::kShooterMotorVoltagePercent); },
          {}).ToPtr()); //Start the shooter motors.
          

  dpadDown.OnTrue(frc2::InstantCommand([&]() -> void
          {m_shooterSubsystem.StopShooter(); },
          {}).ToPtr()); //Stop the shooter motors

  
}
// #pragma endregion

// #pragma region Test
void RobotContainer::TestInit() noexcept
{
  // m_ledSubsystem.TestColor();

  frc2::CommandScheduler::GetInstance().CancelAll();

  m_driveSubsystem.ClearFaults();

  m_driveSubsystem.ResetEncoders();

  m_driveSubsystem.TestInit();

  frc2::CommandScheduler::GetInstance().Enable();
}

void RobotContainer::TestPeriodic() noexcept
{
  m_driveSubsystem.TestPeriodic();
}

void RobotContainer::TestExit() noexcept
{
  frc2::CommandScheduler::GetInstance().CancelAll();

  m_driveSubsystem.ClearFaults();

  m_driveSubsystem.ResetEncoders();

  m_driveSubsystem.TestExit();

  m_driveSubsystem.BurnConfig();
}

frc2::CommandPtr RobotContainer::PointCommandFactory(RobotContainer *container) noexcept
{
  // Set up default drive command; non-owning pointer is passed by value.
  auto driveRequirements = {dynamic_cast<frc2::Subsystem *>(&container->m_driveSubsystem)};

  // Point swerve modules, but do not actually drive.
  return frc2::CommandPtr{std::make_unique<frc2::RunCommand>(
      [container]() -> void
      {
        const auto controls = container->GetDriveTeleopControls();

        units::angle::radian_t angle{std::atan2(std::get<0>(controls), std::get<1>(controls))};

        // Ingnore return (bool); no need to check that commanded angle has
        // been reached.
        (void)container->m_driveSubsystem.SetTurningPosition(angle);
      },
      driveRequirements)};
}
// #pragma endregion

// #pragma region Disabled
void RobotContainer::DisabledInit() noexcept
{
  frc2::CommandScheduler::GetInstance().CancelAll();

  m_driveSubsystem.ClearFaults();

  m_driveSubsystem.ResetEncoders();

  // Useful things may be done disabled... (construct, config, dashboard, etc.)
  frc2::CommandScheduler::GetInstance().Enable();
  
  m_driveSubsystem.DisabledInit();
}

void RobotContainer::DisabledPeriodic() noexcept {}

void RobotContainer::DisabledExit() noexcept
{
  m_driveSubsystem.ClearFaults();

  m_driveSubsystem.ResetEncoders();

  m_driveSubsystem.DisabledExit();
}
// #pragma endregion
