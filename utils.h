#ifndef UTILS_H
#define UTILS_H

#include "buildsystem.h"
#include "language.h"
#include <filesystem>
#include <string>
#include <vector>

class Utils {
public:
  static std::string getUserGitEmail();
  static BuildSystem *fromLanguage(std::string name, Language *lang);
  static std::filesystem::path getHome();
  static std::string sanitizeProjectName(const std::string &projectName);
  static void createFile(const std::filesystem::path &p);
  static void initGit(const std::filesystem::path &p);
  static std::string exec(const char *cmd, int *code);
  static std::vector<std::filesystem::path> getFiles(const std::filesystem::path &p);
};

#endif // UTILS_H
