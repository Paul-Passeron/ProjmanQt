#include "projectmanager.h"
#include "cppproject.h"
#include "qobjectdefs.h"
#include <QMessageBox>
#include <iostream>

ProjectManager::ProjectManager() : current_project(-1) {}

ProjectManager::~ProjectManager() {
  // DO NOTHING FOR NOW
}

Project *ProjectManager::getCurrentProject() {
  if (current_project >= (int)projects.size() || current_project < 0) {
    return nullptr;
  }
  return projects.at(current_project);
}

void ProjectManager::setCurrentProject(std::string name) {

  for (size_t i = 0; i < projects.size(); i++) {
    if (projects.at(i)->getName() == name) {
      current_project = i;
      emit currentProjectChanged();
      return;
    }
  }
}

Project *ProjectManager::fromLanguage(Language *lang, std::string name,
                                      std::string description) {
  std::cout << typeid(*lang).name() << std::endl;
  if (lang->getName() == "C++") {
    return new CppProject(name, description);
  } else {
    QMessageBox::critical(nullptr, "Error", "Failed to find lang");
  }
  return nullptr;
}

void ProjectManager::createProject(Project *project) {
  // maybe make sure that a project with the same name does not already exists
  projects.emplace_back(project);
}

void ProjectManager::deleteProject(std::string name) {
  for (size_t i = 0; i < projects.size(); i++) {
    if (projects.at(i)->getName() == name) {
      projects.erase(projects.begin() + i);
      return;
    }
  }
}

Project *ProjectManager::getProject(std::string name) {
  for (const auto &proj : projects) {
    if (proj->getName() == name) {
      return proj;
    }
  }
  return nullptr;
}
