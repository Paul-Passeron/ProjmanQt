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
  bool operator==(const RunConfiguration &other) const;
  RunConfiguration(const RunConfiguration &rc);
  std::string getName() const;
  std::string getCommand() const;
  bool getNeedsArgs() const;
public slots:
  void execute() const;
signals:
  void started(RunConfiguration rc);
};

#endif // RUNCONFIGURATION_H
