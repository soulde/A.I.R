//
// Created by lyjly on 2022/2/13.
//

#ifndef AIR_APPLICATION_H
#define AIR_APPLICATION_H


#include <QThread>
#include "Core.h"
#include "LoginWindow.h"
#include "MainWindow.h"


class Application :QObject{
    Q_OBJECT
public:
    explicit Application(const std::string& configPath);

    ~Application();

private slots:
    void alternate(int type);


private:

    QThread thread;

    Core* core;

    ExtManager* extManager;

    QWidget *pWindow = nullptr;


};

#endif //AIR_APPLICATION_H
