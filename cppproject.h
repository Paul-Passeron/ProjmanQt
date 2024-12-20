#ifndef CPPPROJECT_H
#define CPPPROJECT_H

#include "project.h"
#include <language.h>

class CppProject : public Project {
public:
  CppProject(std::string name, std::string description,
             std::filesystem::path p);
  void generateFileStructure() override;
};

#endif // CPPPROJECT_H
