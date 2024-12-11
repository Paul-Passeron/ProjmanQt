#ifndef UTILS_H
#define UTILS_H

#include "buildsystem.h"
#include "language.h"

#include <filesystem>
#include <string>
class Utils
{
public:
    static std::string getUserGitEmail();
    static BuildSystem *fromLanguage(std::string name, Language *lang);
    static std::filesystem::path getHome();
};

#endif // UTILS_H
