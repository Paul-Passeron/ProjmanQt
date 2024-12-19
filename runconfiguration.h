#ifndef RUNCONFIGURATION_H
#define RUNCONFIGURATION_H

#include <string>

class RunConfiguration {
  std::string name;
  std::string command;
  bool needs_args;

public:
  RunConfiguration(std::string name, std::string command, bool needs_args);
  std::string getName() const;
  void execute();
  bool getNeedsArgs();
};

#endif // RUNCONFIGURATION_H
