#include "projectmanager.h"
#include "cppproject.h"
#include "languagemanager.h"
#include "qimage.h"
#include "qjsondocument.h"
#include "qjsonvalue.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <filesystem>
#include <fstream>
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
                                      std::string description,
                                      std::filesystem::path p) {
  std::cout << typeid(*lang).name() << std::endl;
  if (lang->getName() == "C++") {
    return new CppProject(name, description, p);
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

Project *ProjectManager::fromSerialized(const std::filesystem::path &p) {
  std::filesystem::path serialized = p / ".projman";
  std::filesystem::path readme = p / "README.md";

  std::string description = "";
  if (std::filesystem::exists(p)) {
    std::ifstream readmefile(readme);
    description = std::string(std::istreambuf_iterator<char>(readmefile),
                              std::istreambuf_iterator<char>());
    readmefile.close();
  }

  QString name;
  QString language;

  // TODO: accomodate for errors

  if (!std::filesystem::exists(p)) {
    // treat it as a blank project
    // should ask the user what language the project is
    std::cout << "no .projman found 1" << std::endl;
    return nullptr;

  } else {

    QFile f = QFile(serialized);
    if (!f.open(QIODevice::ReadOnly)) {
      // could not read .projman file !
      std::cout << "no .projman found 2" << std::endl;

      return nullptr;
    }
    QString jsonData = f.readAll();
    f.close();
    if (!jsonData.startsWith("PROJ")) {
      // not a valid .projman file
      std::cout << "not a valid .projman" << std::endl;
    }

    jsonData.erase(jsonData.begin(), jsonData.begin() + 4);

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &error);
    if (jsonDoc.isNull() || error.error != QJsonParseError::NoError) {
      // could not parse .projman file
      std::cout << "json error" << std::endl;
      std::cout << error.errorString().toStdString() << std::endl;
      return nullptr;
    }
    QJsonObject json = jsonDoc.object();

    if (json.contains("name")) {
      name = json["name"].toString();
    }
    if (json.contains("language")) {
      language = json["language"].toString();
    }
  }
  Language *lang = LanguageManager::fromName(language.toStdString());
  if (lang == nullptr) {
    // could not find language
    std::cout << "could not find language" << std::endl;
    return nullptr;
  }
  // TODO: build system + run configurations
  return ProjectManager::fromLanguage(lang, name.toStdString(), description,
                                      p.parent_path());
}