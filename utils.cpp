#include "utils.h"
#include "qmessagebox.h"
#include <QMessageBox>
#include <algorithm>
#include <filesystem>
#include <fstream>

BuildSystem *Utils::fromLanguage(std::string name, Language *lang) {
  (void)name;
  (void)lang;
  return nullptr;
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

void Utils::initGit(const std::filesystem::path &p) {
  createFile(p / ".gitignore");
  std::string command = "git init ";
  command += p.string();
  int res = system(command.c_str());
  if (res != 0) {
    QMessageBox::critical(nullptr, "Error", "Failed to initialize git");
  }
}

std::string Utils::exec(const char *cmd, int *code) {
  char buff[512] = {0};
  std::string result;
  auto pipe = popen(cmd, "r");
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buff, sizeof(buff), pipe) != nullptr) {
    result += buff;
  }
  *code = WEXITSTATUS(pclose(pipe));
  return result;
}