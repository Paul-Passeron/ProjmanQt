#ifndef BUILDSYSTEM_H
#define BUILDSYSTEM_H

#include <string>

class Project;

class BuildSystem {
  std::string name;

public:
  BuildSystem(std::string name);
  virtual void buildProject(Project *project) = 0;
  virtual void generate(Project *project) = 0;
  virtual void run(Project *project) = 0;
  virtual void clean(Project *project) = 0;
};

#endif // BUILDSYSTEM_H
