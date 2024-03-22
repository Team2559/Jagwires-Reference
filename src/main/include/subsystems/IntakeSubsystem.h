#pragma once

#include "Constants.h"
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>

typedef enum {
  kCurrentHigh,
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
    
private:
    rev::CANSparkMax m_IntakeMotor{intake::kIntakeSpinMotorCanID, rev::CANSparkMax::MotorType::kBrushed};
};
