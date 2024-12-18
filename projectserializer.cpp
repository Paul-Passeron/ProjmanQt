#include "projectserializer.h"
#include "project.h"

std::string ProjectSerializer::serialize(Project *pro) {
  std::string res = "{";
  res += "\"name\" : ";
  res += "\"" + pro->getName() + "\",";
  res += "\"language\" : ";
  res += "\"" + pro->getLanguage()->getName() + "\"";
  res += ",";
  res += "\"run_configurations\" : []";
  res += "}";
  return res;
}
