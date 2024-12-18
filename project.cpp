#include "project.h"
#include "runconfiguration.h"
#include "utils.h"

Project::Project(std::string name, std::string description,
                 std::filesystem::path p)
    : name(name), description(description), p(p) {}

void Project::addFile(std::filesystem::path file) {
  // Check if file is was not already added
  const auto p2 = std::filesystem::path(file);
  for (const auto &f : files) {
    const auto p1 = std::filesystem::absolute(f);
    if (p1 == p2)
      return;
  }
  files.emplace_back(file);
}
void Project::removeFile(std::filesystem::path file) {
  const auto p2 = std::filesystem::path(file);
  for (auto file_it = files.cbegin(); file_it != files.cend(); ++file_it) {
    const auto p1 = std::filesystem::absolute(*file_it);
    if (p1 != p2)
      continue;
    files.erase(file_it);
    return;
  }
}

// If you want to overwrite a run config the right way is to remove the old
// one before ypu add the new one.
void Project::addRunConfiguration(RunConfiguration config) {
  // run configs name should be unique as it is the simplest way to
  // differentiate them
  // checking if a similar run config already exists.
  for (const auto &c : runConfigurations) {
    if (c.getName() == config.getName())
      return;
  }
  runConfigurations.emplace_back(config);
}

void Project::removeRunConfiguration(RunConfiguration config) {
  // run configs name should be unique as it is the simplest way to
  // differentiate them
  for (auto c_it = runConfigurations.cbegin(); c_it != runConfigurations.cend();
       ++c_it) {
    if (c_it->getName() != config.getName())
      continue;
    // We are done because there must be only one (or zero) config with a
    // singular name in this vector.
    runConfigurations.erase(c_it);
    return;
  }
}

std::vector<std::filesystem::path> Project::getFiles() const { return files; }

BuildSystem *Project::getBuildSystem() const { return buildSystem; }

std::string Project::getName() const { return name; }

std::filesystem::path Project::getPath() const { return p; }

std::string Project::getSanitized() {
  return Utils::sanitizeProjectName(getName());
}