#include "cppproject.h"
#include "cpplanguage.h"
#include "makefilebuildsystem.h"
#include <filesystem>
#include <fstream>

CppProject::CppProject(std::string name, std::string description,
                       std::filesystem::path p)
    : Project(name, description, p) {
  this->language = new CppLanguage();
  this->buildSystem = new MakefileBuildSystem();
}

void generateCppSampleMainFile(const std::filesystem::path &p) {
  std::ofstream f(p);
  f << "#include <iostream>" << std::endl;
  f << std::endl;
  f << "int main() {" << std::endl;
  f << "    std::cout << \"Hello, World!\" << std::endl;" << std::endl;
  f << "    return 0;" << std::endl;
  f << "}" << std::endl;
  f.close();
}

void CppProject::generateFileStructure() {
  std::filesystem::path projectPath = this->getPath();
  std::filesystem::path p = projectPath / getSanitized();
  std::filesystem::create_directory(p);
  std::filesystem::create_directory(p / "src");
  std::filesystem::create_directory(p / "include");
  std::filesystem::create_directory(p / "build");
  std::filesystem::create_directory(p / "bin");
  std::filesystem::path main_file = p / "src" / (getSanitized() + ".cpp");
  generateCppSampleMainFile(main_file);
}
