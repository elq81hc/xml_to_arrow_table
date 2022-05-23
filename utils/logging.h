#pragma once 

#include <iostream>
#include <string>
#include <fstream>

namespace logging
{
static std::ostream& Instance() {
    static std::fstream logFile("logFile.json", std::ios::app | std::ios::out);
    return logFile;
}
void logErr(std::string msg) {
    std::cerr << "[error] " << msg << "\n";
}
void logInfo(std::string msg) {
    std::cout << "[info] " << msg << "\n";
}
} // namespace logging
