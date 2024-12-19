#include "projectserializer.h"
#include "project.h"
#include <string>

std::string ProjectSerializer::serialize(Project *pro) {
  std::string res = "{";
  res += "\"name\" : ";
  res += "\"" + pro->getName() + "\",";
  res += "\"language\" : ";
  res += "\"" + pro->getLanguage()->getName() + "\"";
  res += ",";
  res += "\"last_config\": \"" + std::to_string(pro->getLastConfig()) + "\",";
  res += "\"run_configurations\" : [";
  bool start = true;
  for (auto &conf : pro->getConfigs()) {
    if (!start) {
      res += ",";
    }
    start = false;
    res += "{\"name\":\"" + conf.getName() + "\",\"command\":\"" +
           conf.getCommand() + "\", \"needs_args\": \"" +
           (conf.getNeedsArgs() ? "true" : "false") + "\"}";
  }
  res += "]";
  res += "}";
  return res;
}
