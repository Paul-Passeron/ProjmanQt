#ifndef CMAKEBUILDSYSTEM_H
#define CMAKEBUILDSYSTEM_H

#include "buildsystem.h"

class CMakeBuildSystem : public BuildSystem {

public:
  CMakeBuildSystem();
  void generate(Project *project, std::filesystem::path outputDirectory,
                std::string to_add) override;
};

#endif // RUNCONFIGURATION_H
