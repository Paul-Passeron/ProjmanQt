#ifndef PROJECT_H
#define PROJECT_H

#include "buildsystem.h"
#include "language.h"
#include "qtmetamacros.h"
#include "runconfiguration.h"
#include <QObject>
#include <filesystem>
#include <string>

#include <vector>

class Project : public QObject {
  Q_OBJECT

  std::string name;
  std::string description;
  std::filesystem::path p;
  std::vector<RunConfiguration> runConfigurations;
  int last_config = -1;
  bool is_dirty = false;

protected:
  Language *language;
  BuildSystem *buildSystem;

public:
  Project(std::string name, std::string description, std::filesystem::path p);
  ~Project() = default;
  void addRunConfiguration(RunConfiguration config);
  void removeRunConfiguration(RunConfiguration config);
  std::vector<std::filesystem::path> getFiles() const;
  std::vector<RunConfiguration> &getConfigs();
  BuildSystem *getBuildSystem() const;
  std::string getName() const;
  std::string getSanitized();
  std::filesystem::path getPath() const;
  int getLastConfig() const;
  void setLastConfig(const RunConfiguration &rc);
  virtual void generateFileStructure() = 0;
  Language *getLanguage();
  void serialize();
  std::string getDescription() const;
  void setDescription(std::string description);

signals:
  void runConfigurationsChanged();
};

#endif // PROJECT_H
