#include "makefilebuildsystem.h"
#include "project.h"
#include "utils.h"
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <ostream>

MakefileBuildSystem::MakefileBuildSystem() : BuildSystem("make") {}

void MakefileBuildSystem::buildProject(Project *project) {
  (void)project;
  int code;
  std::cout << Utils::exec("make", &code) << std::endl;
  if (code) {
    QMessageBox::critical(nullptr, "Build Failed",
                          "The build failed with code " +
                              QString::fromStdString(std::to_string(code)));
  }
}

void MakefileBuildSystem::generate(Project *project) {
  std::string san = project->getSanitized();
  std::filesystem::path outputDirectory = project->getPath() / san;
  std::ofstream makefile(outputDirectory / "Makefile");
  if (!makefile.is_open()) {
    throw std::runtime_error("Failed to open Makefile for writing");
  }
  makefile << "CC=g++\n";
  makefile << "CXX=g++\n";
  makefile << "CFLAGS=-Wall -Wextra -pedantic\n";
  makefile << "BUILD=build/\n";
  makefile << "SRC=src/\n";
  makefile << "BIN=bin/\n";
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
  makefile << "DEPS=";
  for (const auto &f : Utils::getFiles(project->getPath() / san)) {
    if ((f.extension() == ".c" || f.extension() == ".cpp")) {
      makefile << "$(BUILD)" << f.stem().string() << ".o ";
    }
  }

  makefile << "\n";
  makefile << R"(all: lines )" << san << R"(
lines:
	@echo "C:"
	@wc -l $$( find -wholename './*.[hc]') | tail -n 1
$(BUILD)%.o: $(SRC)%.c
	 $(CC) $(CFLAGS) -o $@ $^ -c
$(BUILD)%.o: $(SRC)%.cpp
	 $(CXX) $(CFLAGS) -o $@ $^ -c
$(BIN))" << san
           << R"(: $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS))"
           << std::endl;
  makefile << san << ": $(BIN)" << san << std::endl;
  makefile << R"(clean:
	rm -rf $(BIN)*
	rm -rf $(BUILD)*)"
           << std::endl;

  makefile.close();
}

void MakefileBuildSystem::run(Project *project) {
  int code;
  std::cout << Utils::exec(("./bin/" + project->getSanitized()).c_str(), &code)
            << std::endl;
  if (code) {
    QMessageBox::critical(nullptr, "Build Failed",
                          "The run failed with code " +
                              QString::fromStdString(std::to_string(code)));
  }
}

void MakefileBuildSystem::clean(Project *project) {
  int code;
  (void)code;
  (void)project;
  Utils::exec("make clean", &code);
}
