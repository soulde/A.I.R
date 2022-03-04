//
// Created by lyjly on 2022/2/28.
//

#ifndef AIR_PATHMANAGER_H
#define AIR_PATHMANAGER_H

#include <sys/stat.h>
#include <string>
#include <map>
#include "yaml-cpp/yaml.h"

class PathManager {
public:
    PathManager(const std::string& config);

    static std::string getValue(const std::string& name);

    static std::string relatedPath2Absolute(std::string root, std::string relatedPath);

private:
    static std::map<std::string, std::string> path;

    inline void registerPath(const std::string& name, std::string value);
};


#endif //AIR_PATHMANAGER_H
