#ifndef RUNCONFIGURATION_H
#define RUNCONFIGURATION_H

#include <QObject>
#include <string>

class RunConfiguration : public QObject {
  Q_OBJECT

  std::string name;
  std::string command;
  bool needs_args;

public:
  RunConfiguration(std::string name, std::string command, bool needs_args);
  bool operator=(const RunConfiguration &other);
  RunConfiguration(const RunConfiguration &rc);
  std::string getName() const;
  bool getNeedsArgs();
public slots:
  void execute();
};

#endif // RUNCONFIGURATION_H
