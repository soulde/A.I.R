//
// Created by lyjly on 2022/1/30.
//

#ifndef AIR_USER_H
#define AIR_USER_H

#include <string>
#include <vector>

class User {
public:
    User() = default;

    std::string ID;
    std::string name;
    enum {
        user,
        admin
    } type = user;

    static std::string index2String(int index);

    static std::vector<std::string> techGroup;
    static std::vector<std::string> adminGroup;
    static std::vector<std::string> grade;

private:

};


#endif //AIR_USER_H
