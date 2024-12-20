#include "languagemanager.h"

#include "clanguage.h"
#include "cpplanguage.h"
#include "language.h"
#include "pythonlanguage.h"

std::vector<Language *> LanguageManager::languages;

LanguageManager::LanguageManager() {}

Language *LanguageManager::fromName(std::string name) {
  getAllLanguages();
  for (const auto &lang : languages) {
    printf("AGAINST: %s\n", lang->getName().c_str());
    if (lang->getName() == name) {
      return lang;
    }
  }
  printf("BAD LANGUAGE NAME: %s\n", name.c_str());
  return nullptr;
}

std::vector<Language *> LanguageManager::getAllLanguages() {
  if (languages.size() == 0) {
    languages.emplace_back(new CppLanguage);
    languages.emplace_back(new CLanguage);
    languages.emplace_back(new PythonLanguage);
  }
  return languages;
}
