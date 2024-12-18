#ifndef PROJECTSERIALIZER_H
#define PROJECTSERIALIZER_H

#include <string>

class Project;


class ProjectSerializer
{
public:
    static std::string serialize(Project *pro);
};

#endif // PROJECTSERIALIZER_H
