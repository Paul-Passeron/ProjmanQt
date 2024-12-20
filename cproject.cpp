#include "cproject.h"

#include "clanguage.h"
#include "makefilebuildsystem.h"
#include <filesystem>
#include <fstream>

CProject::CProject(std::string name, std::string description,
                   std::filesystem::path p)
    : Project(name, description, p) {
  this->language = new CLanguage();
  this->buildSystem = new MakefileBuildSystem();
}

void generateCSampleMainFile(const std::filesystem::path &p) {
  std::ofstream f(p);
  f << "#include <stdio.h>" << std::endl;
  f << std::endl;
  f << "int main(void) {" << std::endl;
  f << "    printf(\"Hello, World!\n\");" << std::endl;
  f << "    return 0;" << std::endl;
  f << "}" << std::endl;
  f.close();
}

void CProject::generateFileStructure() {
  std::filesystem::path projectPath = this->getPath();
  std::filesystem::path p = projectPath / getSanitized();
  std::filesystem::create_directory(p);
  std::filesystem::create_directory(p / "src");
  std::filesystem::create_directory(p / "include");
  std::filesystem::create_directory(p / "build");
  std::filesystem::create_directory(p / "bin");
  std::filesystem::path main_file = p / "src" / (getSanitized() + ".c");
  generateCSampleMainFile(main_file);
}
