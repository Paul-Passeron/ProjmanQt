#include "language.h"

Language::Language(std::string name) : name(name) {}

std::string Language::getName() const { return name; }