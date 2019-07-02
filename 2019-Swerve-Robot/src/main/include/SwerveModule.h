#pragma once

#include <frc/AnalogInput.h>
#include <frc/PIDController.h>

#include <ctre/Phoenix.h>

#include <rev/CANSparkMax.h>

class SwerveModule {
public:
    SwerveModule(int driveMotorId, int pivotMotorId, int pivotSensorId, double zeroAngle);

    // Speed is range [-1.0, 1.0]
    // Angle is in radians
    void Set(double speed, double angle);

    double getAngle() const;

private:
    rev::CANSparkMax m_driveMotor;

    WPI_VictorSPX m_pivotMotor;
    frc::AnalogInput m_pivotSensor;

    frc::PIDController m_pivotController;

    double m_zeroAngle;

    // TODO: Add pivot motor and sensor
};