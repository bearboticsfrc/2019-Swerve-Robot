#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <array>
#include <frc/Timer.h>

namespace logger {
    namespace {
            Level currentLevel = Level::Error;

            // Returns whether or not a message with the given level should be displayed
            // e.g. if we're at Error level, don't display Debug-level messages
            bool shouldPrintAt(Level level) {
                return static_cast< int >(level) > static_cast< int >(currentLevel);
            }
    };

    std::string getPrefix(Level level) {
        static const std::array< std::string, 4 > prefixes = { "[ERR]", "[WRN]", "[INF]", "[DBG]" };

        return prefixes[static_cast< std::size_t >(level)];
    }

    void setLevel(Level level) {
        currentLevel = level;
    }

    void log(const std::string& str, Level msgLevel) {
        if (!shouldPrintAt(msgLevel)) {
            return;
        }

        std::cout << getPrefix(msgLevel) << " ";

        double time = frc::GetTime();

        std::cout << std::setprecision(3) << std::setw(5) << time << ": " << str;
    }
};