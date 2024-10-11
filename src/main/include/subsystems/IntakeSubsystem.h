#pragma once

#include "Constants.h"
#include "rev/CANSparkMax.h"
#include "frc/DigitalInput.h"
#include <frc2/command/SubsystemBase.h>

typedef enum {
  kCurrentHigh,
  kCurrentMed,
  kCurrentLow
} IntakeMotorCurrent;

class IntakeSubsystem : public frc2::SubsystemBase
{
public:
    IntakeSubsystem() noexcept;

    IntakeSubsystem(const IntakeSubsystem &) = delete;
    IntakeSubsystem &operator=(const IntakeSubsystem &) = delete;

    void StopIntake() noexcept;
    void SetSpinMotorCurrent(IntakeMotorCurrent mode) noexcept;
    void SetSpinMotorVoltagePercent(const double percent) noexcept;

    bool HasNote() noexcept;
private:
    rev::CANSparkMax m_IntakeMotor{intake::kIntakeSpinMotorCanID, rev::CANSparkMax::MotorType::kBrushed};

    frc::DigitalInput m_limit1{intake::kIntakeLimit1DIOPort};
    frc::DigitalInput m_limit2{intake::kIntakeLimit2DIOPort};
};
