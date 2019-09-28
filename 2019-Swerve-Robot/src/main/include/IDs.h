#include <array>
#include <tuple>
#include <frc/AnalogInput.h>

namespace ids {
    /* --- Driver Station ---- */
    constexpr const int joystick_port = 0;
    constexpr const int controller_port = 1;

    /* -------- Robot -------- */

    // Don't you love electrical's wiring assignment?
    // Neo port, swivel motor port, swivel sensor port, offset
    #define ENTRY(N, SM, SS, O) std::tuple< int, int, int, double >{ N, SM, SS, O }
    constexpr const std::array< std::tuple< int, int, int, double >, 4 > swerve_train_ids {
        ENTRY(14,  8, 0,  62.0),
        ENTRY(12, 11, 3,  48.0),
        ENTRY( 3,  5, 2, 272.0),
        ENTRY(15,  9, 1, 314.0)
    };

    constexpr const int hatch_manip_extend_port = 3;
    constexpr const int hatch_manip_retract_port = 2;
    constexpr const int hatch_manip_suction_port = 1;

    constexpr const int cargo_manip_angle_motor_port = 4;
    constexpr const int cargo_manip_angle_sensor_port = 4;
    constexpr const int cargo_manip_intake_port = 10;

    constexpr const int elevator_main_port = 1;
    constexpr const int elevator_aux_port = 2;

    constexpr const int vacuum_port = 13;

    constexpr const int gyro_port = 10;
}