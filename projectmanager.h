#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include "project.h"
#include "qobject.h"
#include <string>
#include <vector>

class ProjectManager : public QObject {
  Q_OBJECT
  std::vector<Project *> projects;
  int current_project;
  void loadProjects();

public:
  ProjectManager();
  ~ProjectManager();
  Project *fromLanguage(Language *lang, std::string name,
                        std::string description, std::filesystem::path p);
  void createProject(Project *project);
  void deleteProject(std::string name);
  Project *getProject(std::string name);
  Project *getCurrentProject();
  void setCurrentProject(std::string name);
  Project *fromSerialized(const std::filesystem::path &p);
signals:
  void currentProjectChanged();
};

#endif // PROJECTMANAGER_H
