#include "runconfiguration.h"
#include "qdialog.h"
#include "runargsdialog.h"
#include "utils.h"
#include <QMessageBox>

RunConfiguration::RunConfiguration(std::string name, std::string command,
                                   bool needs_args)
    : name(name), command(command), needs_args(needs_args) {}

std::string RunConfiguration::getName() const { return name; }

void RunConfiguration::execute() {
  if (needs_args) {
    auto diag = new RunArgsDialog();
    if (diag->exec() != QDialog::Accepted) {
      return;
    }
  }
  int code;
  Utils::exec(command.c_str(), &code);
  if (code != 0) {
    QMessageBox::critical(nullptr, QString("Error"),
                          "Command failed with code " +
                              QString::fromStdString(std::to_string(code)));
  }
}

RunConfiguration::RunConfiguration(const RunConfiguration &rc) {
  name = rc.name;
  command = rc.command;
  needs_args = rc.needs_args;
}

bool RunConfiguration::operator=(const RunConfiguration &other) {
  return (name = other.name, command = other.command,
          needs_args = other.needs_args);
}

bool RunConfiguration::operator==(const RunConfiguration &other) const {
  return name == other.name && command == other.command &&
         needs_args == other.needs_args;
}
