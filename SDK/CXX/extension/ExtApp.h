//
// Created by lyjly on 2022/2/26.
//

#ifndef AIR_EXTAPP_H
#define AIR_EXTAPP_H
#include <QApplication>

class ExtApp :QApplication{
public:
    ExtApp(int argc, char** argv);

protected:
    std::string databaseUrl;

    std::string ID;
};


#endif //AIR_EXTAPP_H
