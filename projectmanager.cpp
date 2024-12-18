#include "projectmanager.h"
#include "cppproject.h"
#include "invalidprojectdialog.h"
#include "language.h"
#include "languagemanager.h"
#include "qimage.h"
#include "qjsondocument.h"
#include "qjsonvalue.h"
#include "qmessagebox.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "utils.h"
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

Language *askLang() {
  InvalidProjectDialog *diag = new InvalidProjectDialog();
  if (diag->exec() != QDialog::Accepted) {
    // The user stopped oppening the project
    return nullptr;
  }
  return diag->getLang();
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

  bool good = true;

  // TODO: accomodate for errors
  if (!std::filesystem::exists(serialized)) {
    // treat it as a blank project
    // should ask the user what language the project is
    Language *lang = askLang();
    if (lang == nullptr) {
      return nullptr;
    }
    name = QString::fromStdString(p.filename());
    good = false;
    language = QString::fromStdString(lang->getName());
  } else {

    QFile f = QFile(serialized);
    if (!f.open(QIODevice::ReadOnly)) {
      // could not read .projman file !
      std::cout << "no .projman found 2" << std::endl;

      Language *lang = askLang();
      if (lang == nullptr) {
        return nullptr;
      }
      language = QString::fromStdString(lang->getName());
      name = QString::fromStdString(p.filename());
      good = false;
    }
    QString jsonData = f.readAll();
    f.close();
    if (!jsonData.startsWith("PROJ")) {
      // not a valid .projman file
      Language *lang = askLang();
      if (lang == nullptr) {
        return nullptr;
      }
      language = QString::fromStdString(lang->getName());
      name = QString::fromStdString(p.filename());
      good = false;
    }

    jsonData.erase(jsonData.begin(), jsonData.begin() + 4);

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8(), &error);
    if (jsonDoc.isNull() || error.error != QJsonParseError::NoError) {
      // could not parse .projman file
      Language *lang = askLang();
      if (lang == nullptr) {
        return nullptr;
      }
      name = QString::fromStdString(p.filename());
      good = false;
      language = QString::fromStdString(lang->getName());
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
    Language *lang = askLang();
    if (lang == nullptr) {
      return nullptr;
    }
    name = QString::fromStdString(p.filename());
    good = false;
    language = QString::fromStdString(lang->getName());
  }
  std::string n = name.toStdString();
  if (!good && n != Utils::sanitizeProjectName(n)) {
    QMessageBox::critical(
        nullptr, "Could not load project",
        "This directory name contains one or more illegal characters...");
    return nullptr;
  }
  // TODO: build system + run configurations
  return ProjectManager::fromLanguage(lang, name.toStdString(), description,
                                      p.parent_path());
}
