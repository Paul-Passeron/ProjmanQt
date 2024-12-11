#include "cmakebuildsystem.h"
#include "buildsystem.h"
#include "project.h"
#include "qlogging.h"
#include <fstream>
#include <vector>

CMakeBuildSystem::CMakeBuildSystem() : BuildSystem("cmake") {}

void CMakeBuildSystem::generate(Project *project,
                                std::filesystem::path outputDirectory,
                                std::string to_add) {
  // We suppose that we must overwrite the file if it already
  // exists. Wether or not we must must be determined by the
  // caller
  std::ofstream cmakeFile = std::ofstream(outputDirectory / "CMakeLists.txt");
  if (!cmakeFile.is_open()) {
    qWarning("Could not open CMakeList.txt for writing...\n");
    return;
  }
  cmakeFile << "#PROJMAN\n";
  // This is to indicate to projman that this file was
  // generaetd by it and that it can be overwritten
  cmakeFile << "cmake_minimum_required(VERSION 3.10)\n";
  cmakeFile << "project(" << project->getName() << ")\n";
  cmakeFile << "set(CMAKE_CXX_STANDARD 14)\n";
  cmakeFile << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n";
  cmakeFile << "add_executable(" << project->getName() << "\n";
  std::vector<std::filesystem::path> files = project->getFiles();
  for (const auto &path : files) {
    cmakeFile << "               " << path.string() << "\n";
  }
  cmakeFile << ")\n";
  cmakeFile << to_add;
  cmakeFile.close();
}