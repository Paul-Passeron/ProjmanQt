#ifndef MAKEFILEBUILDSYSTEM_H
#define MAKEFILEBUILDSYSTEM_H

#include "buildsystem.h"

class MakefileBuildSystem : public BuildSystem {
public:
  MakefileBuildSystem();
  void generate(Project *project, std::filesystem::path outputDirectory,
                std::string to_add) override;
};

#endif // MAKEFILEBUILDSYSTEM_H
