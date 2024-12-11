#include "cppproject.h"

#include "cpplanguage.h"

CppProject::CppProject(std::string name, std::string description): Project(name, description) {
    this->language = new CppLanguage();
}
