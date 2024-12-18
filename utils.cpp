#include "utils.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>

BuildSystem *Utils::fromLanguage(std::string name, Language *lang) {
  (void)name;
  (void)lang;
  std::runtime_error("TODO: BuildSystem *Utils::fromLanguage(std::string name, "
                     "Language *lang)");
  // return nullptr;
}

std::filesystem::path Utils::getHome() {
  std::filesystem::path p = std::filesystem::current_path();
  return p.root_path();
}

std::string Utils::sanitizeProjectName(const std::string &projectName) {
  std::string sanitized = projectName;

  // remove trailing whitespaces
  const std::string whitespaces = " \t\n\r\f\v";
  sanitized.erase(0, sanitized.find_first_not_of(whitespaces));
  sanitized.erase(sanitized.find_last_not_of(" \t\n\r\f\v") + 1);

  // replacing every invalid characters with '_'
  const std::string invalidChars = "\\/:*?\"<>|!@=+-" + whitespaces;
  for (char &ch : sanitized) {
    if (invalidChars.find(ch) != std::string::npos) {
      ch = '_';
    }
  }

  if (sanitized.empty()) {
    sanitized = "default_project";
  }

  std::transform(sanitized.begin(), sanitized.end(), sanitized.begin(),
                 ::tolower);

  return sanitized;
}

void Utils::createFile(const std::filesystem::path &p) {
  std::ofstream f(p);
  f.close();
}