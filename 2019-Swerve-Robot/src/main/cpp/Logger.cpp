#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <array>
#include <frc/Timer.h>
#include <time.h>

namespace logger {
    namespace {
            Level currentLevel = Level::Error;

            // Returns whether or not a message with the given level should be displayed
            // e.g. if we're at Error level, don't display Debug-level messages
            bool shouldPrintAt(Level level) {
                return static_cast< int >(level) > static_cast< int >(currentLevel);
            }
    }

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

        time_t temp = time;
        struct tm *tm = localtime(&temp);
        char t[20];
        strftime(t, sizeof(t), "%M:%S", tm);

        std::cout << t << "." << std::setprecision(3) << time - (long)time << ": " << str << '\n';
    }
}