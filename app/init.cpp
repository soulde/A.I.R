//
// Created by lyjly on 2022/3/4.
//
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "DatabaseSQLite.h"

void initConfig(std::string path) {
    YAML::Node config;
    try {
        config = YAML::LoadFile(path);
    } catch (YAML::BadFile &e) {
        std::ofstream fout(path);
        //TODO run init program
        config["database"]["type"] = "sqlite3";
        config["database"]["url"] = "./data/AIR.db";

        config["extensionDir"] = "./extension";

        config["executableDir"]["python"] = "./scripts/python";
        config["executableDir"]["exe"] = "./bin";

        config["interpreter"]["python"] = "./bin/python/pythonw.exe";
        config["interpreter"]["exe"] = "";

        fout << config << std::endl;
        fout.close();
    }
}

void initDatabase(const std::string& dbName) {
    DatabaseSQLite db("../data/" + dbName);
    Query q;
    q.prepareCmd("SELECT name FROM sqlite_master WHERE name='table_name'", db);
    q.read();
    std::string str = q.getData<std::string>(0);
    if (str.empty()) {
        db.executeCmd(
                "CREATE TABLE names ("
                "ID         STRING PRIMARY KEY NOT NULL,"
                "Name       STRING NOT NULL,"
                "School     STRING,Grade      STRING,"
                "TechGroup  STRING DEFAULT 无,"
                "AdminGroup STRING DEFAULT 无,"
                "QQ         STRING,"
                "Tel        STRING,"
                "Password   STRING,"
                "Sex        STRING DEFAULT 未设置)");
        db.executeCmd(
                "CREATE TABLE [score record] ("
                "[Index]  INT    PRIMARY KEY, "
                "ID       STRING NOT NULL CONSTRAINT FK_names_score_record_ID REFERENCES names (ID) ON DELETE CASCADE ON UPDATE CASCADE MATCH [FULL] NOT DEFERRABLE INITIALLY IMMEDIATE,"
                "Score    DOUBLE NOT NULL DEFAULT (0),"
                "Tips     STRING,Operator STRING NOT NULL,"
                "Time     DATE   NOT NULL)"
        );
        db.executeCmd("insert into names (ID, Name, Password) values ('_0','AIR', 'alliance')");
    }
}

int main(int argc, char **argv) {
    std::string configPath;

    configPath= "../data/config.air";
    initConfig(configPath);
    initDatabase("AIR.db");

    return 0;
}