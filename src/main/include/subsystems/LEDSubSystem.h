// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"

// #include "frc/motorcontrol/PWMSparkMax.h"
// #include <frc/motorcontrol/Spark.h>
// #include "frc/motorcontrol/PWMMotorController.h"
#include "frc/PWM.h"
#include "frc/DigitalOutput.h"
// #include <frc/AddressableLED.h>
#include <array>
#include <units/time.h>

#include "Constants.h" 

class LEDSubsystem : public frc2::SubsystemBase {
 public:
  LEDSubsystem() noexcept;

  void NormalColor() noexcept;

  void AllianceColor() noexcept;

  void NoteColor() noexcept;
  
  void StartColor() noexcept;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  inline void SetColor(units::second_t pusleWidth);

  //Create the PWMSparkMax instance
  frc::PWM LEDStrip{1};



};
