//
// Created by lyjly on 2022/2/13.
//


#include "ExtManager.h"

#include <utility>


ExtManager::ExtManager(std::string extensionDir) {
    root = std::move(extensionDir);

    std::vector<std::string> dirs;
    searchDir(root, dirs);
    for (const auto &dir :dirs) {
        try {
            YAML::Node node = YAML::LoadFile(root + "/" + dir + "/info.ext");
            std::string name = node["name"].as<std::string>();
            if (name.empty()) {
                continue;
            }

            apps[name] = dir;
        } catch (YAML::BadFile &e) {
            continue;
        }
    }
}

ExtManager::ExtManager() {

}

std::string ExtManager::runApp(const std::string &name, const std::string &ID) {
    std::string errMsg;
    std::thread t(&ExtManager::run, this, name, ID, std::ref(errMsg));
    t.detach();
    try {
        if (expPtr) {

            std::rethrow_exception(expPtr);
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    usleep(1000);
    return errMsg;
}

void ExtManager::searchDir(const std::string &path, std::vector<std::string> &dirs) {
    _finddata_t data{};
    intptr_t ret = _findfirst((path + "/*").c_str(), &data);

    if (ret == -1) {

        return;
    }
    do {
        if ((data.attrib & _A_SUBDIR)
            && strcmp(data.name, ".") != 0
            && strcmp(data.name, "..") != 0
                ) {

            dirs.emplace_back(data.name);
        }
    } while (_findnext(ret, &data) == 0);
}

std::string ExtManager::getDescription(const std::string &name) {
    std::string dir = apps[name];
    YAML::Node node = YAML::LoadFile(root + "/" + dir + "/info.ext");
    if (node.IsNull()) {
        return std::string("");
    }
    std::string des;
    try {
        des = node["description"].as<std::string>();
    } catch (std::exception &e) {
        des = "";
    }

    std::string tmp = PathManager::relatedPath2Absolute(root + "/" + dir + "/", des);
    return tmp;
}

void ExtManager::getAppList(std::vector<std::string> &appList) {
    for (const auto &item : apps) {
        appList.push_back(item.first);
    }
}

void ExtManager::run(const std::string &name, const std::string &ID, std::string& errMsg) {
    auto dirIter = apps.find(name);
    if (apps.end() == dirIter) {
        return;
    }
    std::string dir = apps[name];
    YAML::Node node = YAML::LoadFile(root + "/" + dir + "/info.ext");
    std::string app, type, url;
    try {
        app = node["executable"].as<std::string>();

    } catch (std::exception &e) {
        return;
    }

    try {
        type = node["type"].as<std::string>();
    } catch (std::exception &e) {
        type = "exe";
    }
    if (type == "python") {
        url = PathManager::getValue("pythonInterpreter") + " " +
              PathManager::relatedPath2Absolute(PathManager::getValue("pythonExecutableDir"), app);
    } else if (type == "exe") {
        url = PathManager::relatedPath2Absolute(PathManager::getValue("exeExecutableDir"), app);
    }

    url = url + (" " + ID + " " + PathManager::getValue("databaseUrl"));
    STARTUPINFO si = {sizeof(STARTUPINFO)};//在产生子进程时，子进程的窗口相关信息
    PROCESS_INFORMATION pi;                  //子进程的ID/线程相关信息
    DWORD returnCode;//用于保存子程进的返回值;
    BOOL bRet = CreateProcess(NULL, (LPSTR) url.c_str(), NULL, NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (bRet) {
        WaitForSingleObject(pi.hProcess, -1);

        GetExitCodeProcess(pi.hProcess, &returnCode);

    } else {
      errMsg = url;
    }
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}

