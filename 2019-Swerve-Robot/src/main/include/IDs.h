#include <array>
#include <tuple>

namespace ids {
    /* --- Driver Station ---- */
    constexpr const int joystick_port = 0;
    constexpr const int controller_port = 1;

    /* -------- Robot -------- */

    // Don't you love electrical's wiring assignment?
    // Neo port, swivel motor port, swivel sensor port, offset
    #define ENTRY(N, SM, SS, O) std::tuple< int, int, int, double >{ N, SM, SS, O }
    constexpr const std::array< std::tuple< int, int, int, double >, 4 > swerve_train_ids {
        ENTRY(14,  8, 0,   2.0),
        ENTRY(12, 11, 3,  54.0),
        ENTRY( 3,  5, 2, 272.0),
        ENTRY(15,  9, 1, 203.0)
    };

    constexpr const int gyro_port = 10;
}