#include "utils.h"
#include <stdexcept>

BuildSystem *Utils::fromLanguage(std::string name, Language *lang)
{
    (void) name;
    (void) lang;
    std::runtime_error("TODO: BuildSystem *Utils::fromLanguage(std::string name, Language *lang)");
    return nullptr;
}

std::filesystem::path Utils::getHome(){
    std::filesystem::path p = std::filesystem::current_path();
    return p.root_path();
}
