#include "pythonproject.h"
#include "pythonlanguage.h"
#include "utils.h"
#include "pythonbuildsystem.h"
#include <fstream>

PythonProject::PythonProject(std::string name, std::string description,
                             std::filesystem::path p)
    : Project(name, description, p) {
  this->language = new PythonLanguage();
    this->buildSystem = new PythonBuildSystem();
}

void generateSampleFile(const std::filesystem::path &p) {
  std::ofstream f(p);
  f << "def main():" << std::endl;
  f << "    print(\"Hello, World !\")" << std::endl;
  f << std::endl;
  f << "if __name__ == \"__main__\":" << std::endl;
  f << "    main()" << std::endl;
  f.close();
}

void generateJupyterSample(const std::filesystem::path &p) {
  std::ofstream f(p);
  f << R"(
{
 "cells": [
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "vscode": {
     "languageId": "plaintext"
    }
   },
   "outputs": [],
   "source": [
    "print(\"Hello, World !\") "
   ]
  }
 ],
 "metadata": {
  "language_info": {
   "name": "python"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 2
}
)";
  f.close();
}

void PythonProject::generateFileStructure() {
  std::filesystem::path projectPath = this->getPath();
  std::filesystem::path p = projectPath / getSanitized();
  std::filesystem::create_directory(p);

  std::filesystem::create_directory(p / "data");
  std::filesystem::create_directory(p / "notebooks");
  std::filesystem::create_directory(p / "reports");
  std::filesystem::create_directory(p / "src");
  std::filesystem::create_directory(p / "tests");

  Utils::createFile(p / "config.yaml");
  Utils::createFile(p / "LICENSE");
  Utils::createFile(p / "requirements.txt");

  generateSampleFile(p / "src/main.py");
  generateSampleFile(p / "notebooks/main.ipynb");
}
