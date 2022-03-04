//
// Created by lyjly on 2022/1/30.
//

#include "User.h"

std::vector<std::string> User::techGroup = {"机械组", "电控组", "视觉组", "硬件组", "宣传组"};

std::vector<std::string> User::adminGroup = {"无", "办公部", "督察部", "宣传部", "机械组", "电控组", "视觉组", "硬件组", "宣传组", "主席团"};



std::vector<std::string> User::grade = {"无", "干事", "副部长", "部长", "副主席", "主席"};

std::string User::index2String(int index) {
    int indexes[3];

    for(auto i:indexes){
        i = index%10;
        index/=10;
    }
    std::string ret = techGroup[indexes[2]];
    if(indexes[1]){
        ret += ", " + adminGroup[indexes[1]];
    }
    if(indexes[2]){
        ret +=adminGroup[indexes[0]];
    }
    return ret;
}


