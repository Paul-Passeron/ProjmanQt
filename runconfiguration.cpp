#include "runconfiguration.h"

RunConfiguration::RunConfiguration(std::string name, std::string command)
    : name(name), command(command) {}

std::string RunConfiguration::getName() const { return name; }