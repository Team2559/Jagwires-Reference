#include "subsystems/IntakeSubsystem.h"
#include <units/voltage.h>

IntakeSubsystem::IntakeSubsystem() noexcept
{
    m_IntakeMotor.SetInverted(intake::kIntakeSpinMotorIsInverted);
    StopIntake();
}

void IntakeSubsystem::StopIntake() noexcept
{
    m_IntakeMotor.StopMotor();
}

void IntakeSubsystem::SetSpinMotorCurrent(IntakeMotorCurrent mode) noexcept
{
    switch (mode) {
    case kCurrentHigh:
        m_IntakeMotor.SetSmartCurrentLimit(80);
        break;
    case kCurrentMed:
        m_IntakeMotor.SetSmartCurrentLimit(80);
    case kCurrentLow:
        m_IntakeMotor.SetSmartCurrentLimit(30);
    }
}

void IntakeSubsystem::SetSpinMotorVoltagePercent(const double percent) noexcept
{
    m_IntakeMotor.Set(percent);
}

bool IntakeSubsystem::HasNote() noexcept
{
    return m_limit1.Get() || m_limit2.Get();
}
