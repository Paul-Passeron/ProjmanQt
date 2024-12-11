#ifndef BUILDSYSTEM_H
#define BUILDSYSTEM_H

#include <filesystem>

class Project;

class BuildSystem {
  std::string name;

public:
  BuildSystem(std::string name);
  void buildProject(Project project);
  virtual void generate(Project *project, std::filesystem::path outputDirectory,
                        std::string to_add) = 0;
};

#endif // BUILDSYSTEM_H
