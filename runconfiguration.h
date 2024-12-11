#ifndef RUNCONFIGURATION_H
#define RUNCONFIGURATION_H

#include <string>

class RunConfiguration {
  std::string name;
  std::string command;

public:
  RunConfiguration(std::string name, std::string command);
  std::string getName() const;
  void execute();
};

#endif // RUNCONFIGURATION_H
