//
// Created by lyjly on 2022/2/13.
//

#ifndef AIR_EXTMANAGER_H
#define AIR_EXTMANAGER_H

#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <yaml-cpp/yaml.h>
#include <windows.h>
#include "Tools.hpp"
#include "PathManager.h"
#include <thread>

class ExtManager {
public:
    ExtManager();

    ExtManager(std::string extensionDir);

    std::string getDescription(const std::string &name);

    void getAppList(std::vector<std::string> &appList);

    std::string runApp(const std::string &name, const std::string &ID);

    inline void setInterpreter(const std::string& type, std::string path){
        interpreterPath[type] = std::move(path);
    }

private:
    void searchDir(const std::string &path, std::vector<std::string> &dirs);

    void run(const std::string &name, const std::string &ID, std::string& errMsg);

    std::string root;

    std::exception_ptr expPtr;

    std::map<std::string, std::string> apps;

    std::map<std::string, std::string> interpreterPath;
};


#endif //AIR_EXTMANAGER_H
