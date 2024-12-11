#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include "language.h"

#include <vector>
class LanguageManager {
protected:
  static std::vector<Language *> languages;

public:
  LanguageManager();
  static Language *fromName(std::string name);
  static std::vector<Language *> getAllLanguages();
};

#endif // LANGUAGEMANAGER_H
