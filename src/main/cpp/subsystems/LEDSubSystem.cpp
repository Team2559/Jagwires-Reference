// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/LEDSubsystem.h"
#include "RevBlinkin.h"
#include <frc/DriverStation.h>

using namespace Blinkin;

LEDSubsystem::LEDSubsystem() noexcept = default;

// This method will be called once per scheduler run
void LEDSubsystem::Periodic() {
}

inline void LEDSubsystem::SetColor(units::second_t pulseWidth) {
    LEDStrip.SetPulseTime(pulseWidth);
}

void LEDSubsystem::NormalColor() noexcept {
    SetColor(Solid::WHITE);
}

void LEDSubsystem::AllianceColor() noexcept {
    using enum frc::DriverStation::Alliance;
    if (auto ally = frc::DriverStation::GetAlliance()) {
        if (ally.value() == kRed) {
            SetColor(Solid::RED);
        } else if (ally.value() == kBlue) {
            SetColor(Solid::BLUE);
        } else {
            SetColor(Solid::GRAY);
        }
    } else {
        SetColor(Solid::VIOLET);
    }
}

void LEDSubsystem::NoteColor() noexcept {
    SetColor(PalletePattern::TWINKLES + PalleteThemes::FOREST_THEME);
}
