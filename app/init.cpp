//
// Created by lyjly on 2022/3/4.
//
#include <yaml-cpp/yaml.h>
#include <fstream>

int main(int argc, char** argv){
    std::string configPath;
    if(argc == 2){
        configPath = std::string(argv[1]);
    }
    else{
        return -1;
    }
    YAML::Node config;
    try {
        config = YAML::LoadFile(configPath);
    } catch (YAML::BadFile &e) {
        std::ofstream fout(configPath);
        //TODO run init program
        config["database"]["type"] = "sqlite3";
        config["database"]["url"] = "./data/AIR.db";

        config["extension"] = "./extension";

        config["executableDir"]["python"] = "./scripts/python";
        config["executableDir"]["exe"] = "./bin";

        config["interpreter"]["python"] = "./bin/python/pythonw.exe";
        config["interpreter"]["exe"] = "";

        fout << config << std::endl;
        fout.close();
    }

    return 0;
}