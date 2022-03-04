//
// Created by lyjly on 2022/2/28.
//

#include "PathManager.h"

std::map<std::string, std::string> PathManager::path;

PathManager::PathManager(const std::string &config) {
    char *str;
    str = getcwd(nullptr, 0);
    registerPath("mainDir", relatedPath2Absolute(std::string(str), "../"));
    free(str);
    try {
        YAML::Node node = YAML::LoadFile(config);
        registerPath("databaseType", relatedPath2Absolute(getValue("mainDir"),node["database"]["type"].as<std::string>()));
        registerPath("databaseUrl", relatedPath2Absolute(getValue("mainDir"),node["database"]["url"].as<std::string>()));

        registerPath("extensionDir", relatedPath2Absolute(getValue("mainDir"),node["extensionDir"].as<std::string>()));

        registerPath("pythonExecutableDir", relatedPath2Absolute(getValue("mainDir"),node["executableDir"]["python"].as<std::string>()));
        registerPath("exeExecutableDir", relatedPath2Absolute(getValue("mainDir"),node["executableDir"]["exe"].as<std::string>()));

        registerPath("pythonInterpreter", relatedPath2Absolute(getValue("mainDir"),node["interpreter"]["python"].as<std::string>()));
        registerPath("exeInterpreter", node["interpreter"]["exe"].as<std::string>());

    } catch (const std::exception &e) {
        throw e;
    }



}

void PathManager::registerPath(const std::string &name, std::string value) {
    path[name] = std::move(value);
}

std::string PathManager::getValue(const std::string &name) {
    return path[name];
}



std::string PathManager::relatedPath2Absolute(std::string root, std::string relatedPath) {
    {
        const std::string div = "\\";
        std::string pp = "..\\";

        size_t ret = 0;
        size_t len = relatedPath.size();

        for (ret = 0;; relatedPath = relatedPath.substr(ret + 3)) {
            if (relatedPath.find(pp) == -1) {
                pp = "../";
            } else {
                pp = "..\\";
            }
            if (relatedPath.find(pp) == -1) {

                if ((ret = relatedPath.find_first_of("./")) == 0) {
                    return root + relatedPath.substr(ret + 1);
                }
                if ((ret = relatedPath.find_first_of(".\\")) == 0) {
                    return root + relatedPath.substr(ret + 1);
                }
                return root + "/" + relatedPath;
            }

            ret = relatedPath.find_first_of(pp);
            if (ret == -1) {
                break;
            }

            size_t i = root.find_last_of(div);
            if (i == -1)
                return std::string();
            else {
                root = root.substr(0, i);
            }
        }
        if (len == relatedPath.size()) {
            return relatedPath;
        } else {
            return root + "\\" + relatedPath;
        }

    }
}
