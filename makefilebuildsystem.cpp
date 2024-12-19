#include "makefilebuildsystem.h"
#include "project.h"
#include <fstream>
#include <istream>
#include <ostream>

MakefileBuildSystem::MakefileBuildSystem() : BuildSystem("make") {}

void MakefileBuildSystem::generate(Project *project,
                                   std::filesystem::path outputDirectory,
                                   std::string to_add) {
  std::ofstream makefile(outputDirectory / "Makefile");
  if (!makefile.is_open()) {
    throw std::runtime_error("Failed to open Makefile for writing");
  }
  makefile << "CC=g++\n";
  makefile << "CXX=g++\n";
  makefile << "CFLAGS=-Wall -Wextra -pedantic\n";
  makefile << "BUILD=build/\n";
  std::ifstream libs(project->getPath() / ".projman.lib");
  if (libs.is_open()) {
    libs.seekg(0, libs.end);
    size_t length = libs.tellg();
    libs.seekg(0, libs.beg);

    char *buffer = new char[length];
    libs.read(buffer, length);
    libs.close();
    makefile << "LIBS=" << buffer << "\n";
    delete[] buffer;
  }
  makefile << "OBJ=";
  // for (const auto &f : project->getFiles()) {
  //   if (f.extension() == ".c") {
  //     makefile << "$(BUILD)" << f.stem().string() << ".o ";
  //   }
  // }
  makefile << "\n";
  makefile.close();
}
