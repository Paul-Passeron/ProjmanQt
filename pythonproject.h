#ifndef PYTHONPROJECT_H
#define PYTHONPROJECT_H

#include "project.h"
#include <language.h>

class PythonProject : public Project {
public:
  PythonProject(std::string name, std::string descritption,
                std::filesystem::path p);
  void generateFileStructure() override;
};

#endif // PYTHONPROJECT_H
