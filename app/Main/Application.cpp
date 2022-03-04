//
// Created by lyjly on 2022/2/13.
//

#include "Application.h"

Application::Application(const std::string &configPath) {
    core = new Core(configPath);

    core->moveToThread(&thread);
    thread.start();
    QObject::connect(core, SIGNAL(alterWindowSignal(int)), SLOT(alternate(int)));
    alternate(LOGIN);

}

Application::~Application() {
    thread.quit();
    delete core;
    thread.wait();

}

void Application::alternate(int type) {
    if (pWindow != nullptr) {
        pWindow->close();
        delete pWindow;
        pWindow = nullptr;
    }
    switch (type) {
        case LOGIN: {
            pWindow = new LoginWindow;
            QObject::connect(pWindow, SIGNAL(loginSignal(const QString&, const QString&)), core,
                             SLOT(login(const QString&, const QString&)));
            QObject::connect(core, SIGNAL(messageSignal(const QString&)), pWindow, SLOT(messageSlot(const QString&)));

        }
            break;
        case MAIN: {
            pWindow = new MainWindow;
            qRegisterMetaType<QList<QString>>("QList<QString>");
            qRegisterMetaType<QList<QString>>("QList<QString>&");
            QObject::connect(core, SIGNAL(userAccessSignal(const QString&, const QString&, bool)), pWindow,
                             SLOT(userSetWindow(const QString&, const QString&, bool)));
            QObject::connect(core, SIGNAL(recordTableSignal(char * *, int, int, double)), pWindow,
                             SLOT(userSetTable(char * *, int, int, double)));
            QObject::connect(pWindow, SIGNAL(rollbackSignal()), core, SLOT(resetLogin()));
            QObject::connect(pWindow, SIGNAL(refreshSignal(const QString&)), core, SLOT(refresh(const QString&)));
            QObject::connect(core, SIGNAL(nameWidgetSignal(char * *, int)), pWindow,
                             SLOT(setSearchTableWidget(char * *, int)));
            QObject::connect(core, SIGNAL(listWidgetSignal(const QList<QString> &)), pWindow,
                             SLOT(setAppList(const QList<QString>& )));
            QObject::connect(core, SIGNAL(appDescriptionSignal(const QString &)), pWindow,
                             SLOT(setDescription(const QString&)));
            QObject::connect(pWindow, SIGNAL(requestDescriptionSignal(const QString&)), core,
                             SLOT(sendAppDescription(const QString&)));
            QObject::connect(pWindow, SIGNAL(runAppSignal(const QString&)), core, SLOT(runApp(const QString&)));
            QObject::connect(core, SIGNAL(messageSignal(const QString&)), pWindow, SLOT(messageSlot(const QString&)));
        }
            break;
    }
    pWindow->show();
    core->waitCondition.wakeAll();
}