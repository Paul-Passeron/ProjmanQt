#ifndef PYTHONBUILDSYSTEM_H
#define PYTHONBUILDSYSTEM_H

#include "buildsystem.h"

class PythonBuildSystem : public BuildSystem {
public:
  PythonBuildSystem();
  void buildProject(Project *project) override;
  void generate(Project *project) override;
  void run(Project *project) override;
  void clean(Project *project) override;
};

#endif // PYTHONBUILDSYSTEM_H
