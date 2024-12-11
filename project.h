#ifndef PROJECT_H
#define PROJECT_H

#include "buildsystem.h"
#include "language.h"
#include "runconfiguration.h"
#include <filesystem>
#include <string>
#include <vector>

class Project {
  std::string name;
  std::string description;
  std::filesystem::path p;
  std::vector<std::filesystem::path> files;
  BuildSystem *buildSystem;
  std::vector<RunConfiguration> runConfigurations;

protected:
  Language *language;

public:
  Project(std::string name, std::string description);
  void addFile(std::filesystem::path file);
  void removeFile(std::filesystem::path file);
  void addRunConfiguration(RunConfiguration config);
  void removeRunConfiguration(RunConfiguration config);
  std::vector<std::filesystem::path> getFiles() const;
  BuildSystem *getBuildSystem() const;
  std::string getName() const;
  std::filesystem::path getPath() const;
};

#endif // PROJECT_H
