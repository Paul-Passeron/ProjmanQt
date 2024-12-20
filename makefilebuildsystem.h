#ifndef MAKEFILEBUILDSYSTEM_H
#define MAKEFILEBUILDSYSTEM_H

#include "buildsystem.h"
#include "project.h"

class MakefileBuildSystem : public BuildSystem {
public:
  MakefileBuildSystem();
  void buildProject(Project *project) override;
  void generate(Project *project) override;
  void run(Project *project) override;
  void clean(Project *project) override;
};

#endif // MAKEFILEBUILDSYSTEM_H
