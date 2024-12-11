#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>

class Language {
protected:
  std::string name;

public:
  Language(std::string name);
  std::string getName() const;
};

#endif // LANGUAGE_H
