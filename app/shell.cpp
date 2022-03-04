#include <iostream>
#include "Core.h"

int main() {
    User *current = nullptr;
    AIR::Core* core = AIR::Core::sysInit();
    std::string name, ID;
    do {
        std::cout << "输入学号和姓名：" << std::endl;
        std::cout << "学号：";
        std::cin >> ID;
        std::cout << "姓名：";
        std::cin >> name;
        current = AIR::Core::login(name, ID);
    } while (current == nullptr);

    return 0;
}
