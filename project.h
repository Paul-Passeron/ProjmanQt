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
  int last_config = -1;

protected:
  Language *language;

public:
  Project(std::string name, std::string description, std::filesystem::path p);
  void addFile(std::filesystem::path file);
  void removeFile(std::filesystem::path file);
  void addRunConfiguration(RunConfiguration config);
  void removeRunConfiguration(RunConfiguration config);
  std::vector<std::filesystem::path> getFiles() const;
  BuildSystem *getBuildSystem() const;
  std::string getName() const;
  std::string getSanitized();
  std::filesystem::path getPath() const;
  RunConfiguration getLastConfig() const;
  void setLastConfig(RunConfiguration &rc);
  virtual void generateFileStructure() = 0;
  Language *getLanguage();
  void serialize();
  std::string getDescription() const;
};

#endif // PROJECT_H
