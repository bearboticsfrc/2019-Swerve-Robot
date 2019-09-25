#pragma once
#include <string>

namespace logger {
    enum class Level { Error, Warning, Info, Debug };

    // Sets the lowest level of priority that should be displayed
    void setLevel(Level level);

    // Adds a new message with the given level
    void log(const std::string& str, Level msgLevel);
}