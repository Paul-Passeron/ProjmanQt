#include "pythonbuildsystem.h"
#include "buildsystem.h"
#include "project.h"
#include "utils.h"

PythonBuildSystem::PythonBuildSystem() : BuildSystem("py") {}

void PythonBuildSystem::buildProject(Project *project) {
  (void)project;
  return;
}

void PythonBuildSystem::generate(Project *project) {
  (void)project;
  return;
}

void PythonBuildSystem::run(Project *project) {
  (void)project;
  std::string command = "python src/main.py";
  int code;
  (void)code;
  Utils::exec(command.c_str(), &code);
}

void PythonBuildSystem::clean(Project *project) {
  (void)project;
  return;
}
