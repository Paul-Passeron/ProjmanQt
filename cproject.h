#ifndef CPROJECT_H
#define CPROJECT_H

#include "project.h"
#include <language.h>

class CProject : public Project {
public:
  CProject(std::string name, std::string description, std::filesystem::path p);
  void generateFileStructure() override;
};

#endif // CPROJECT_H
