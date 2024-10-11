#pragma once

#include "Constants.h"
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>

class TransferArmSubsystem : public frc2::SubsystemBase
{
public:
    TransferArmSubsystem() noexcept;

    TransferArmSubsystem(const TransferArmSubsystem &) = delete;
    TransferArmSubsystem &operator=(const TransferArmSubsystem &) = delete;

    void StopTransferArm() noexcept;
    void SetArmMotorVoltagePercent(const double percent) noexcept;
    units::turn_t GetTransferArmPosition() noexcept;

    void LockBreak() noexcept;
    void ReleaseBreak() noexcept;

private:
    rev::CANSparkMax m_TransferArmMotor{arm::kTransferArmMotorCanID, rev::CANSparkMax::MotorType::kBrushless};
    rev::SparkAbsoluteEncoder m_encoder = m_TransferArmMotor.GetAbsoluteEncoder(rev::SparkAbsoluteEncoder::Type::kDutyCycle);
    // rev::SparkMaxAlternateEncoder m_encoder = m_TransferArmMotor.GetAlternateEncoder(8192);
};
