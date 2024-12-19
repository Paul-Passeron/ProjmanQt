#include "project.h"
#include "projectserializer.h"
#include "runconfiguration.h"
#include "utils.h"
#include <fstream>
#include <iostream>

Project::Project(std::string name, std::string description,
                 std::filesystem::path p)
    : name(name), description(description), p(p), last_config(-1) {}

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
  emit runConfigurationsChanged();
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
    emit runConfigurationsChanged();
  }
}

BuildSystem *Project::getBuildSystem() const { return buildSystem; }

std::string Project::getName() const { return name; }

std::filesystem::path Project::getPath() const { return p; }

Language *Project::getLanguage() { return language; }

std::string Project::getSanitized() {
  return Utils::sanitizeProjectName(getName());
}

void Project::serialize() {
  is_dirty = false;
  // serialize the project
  std::ofstream file(p / getSanitized() / ".projman");
  file << "PROJ"; // 4 magic bytes
  file << ProjectSerializer::serialize(this);
  file.close();
  std::ofstream readme(p / getSanitized() / "README.md");
  readme << description;
  readme.close();
}

std::string Project::getDescription() const { return description; }

std::vector<RunConfiguration> &Project::getConfigs() {
  return runConfigurations;
}

void Project::setDescription(std::string description) {
  is_dirty = true;
  this->description = description;
}

void Project::setLastConfig(const RunConfiguration &rc) {
  int i = 0;
  for (const auto &conf : runConfigurations) {
    if (conf == rc) {
      last_config = i;
      break;
    }
    i++;
  }
  std::cout << "Set last config at " << last_config << std::endl;
}

int Project::getLastConfig() const { return last_config; }
