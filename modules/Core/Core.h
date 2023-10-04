//
// Created by lyjly on 2022/2/7.
//

#ifndef ACPS_CORE_H
#define ACPS_CORE_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <fstream>
#include <pthread.h>

#include "PathManager.h"
#include "DatabaseSQLite.h"
#include "ExtManager.h"
#include "../User/User.h"

enum State {
    LOGIN,
    MAIN,
};

class Core : public QObject {

Q_OBJECT

signals:
    void switchStateSignal(int type);

    void userAccessSignal(const QString &ID, const QString &name, bool isAdmin);

    void recordTableSignal(char **pData, int rows, int cols, double score);

    void nameWidgetSignal(char **pUser, int userNum);

    void listWidgetSignal(const QList<QString>& appList);

    void appDescriptionSignal(const QString& url);

    void messageSignal(const QString& message);

public slots:

    /*!
     * @brief login work function (QT slot)
     * @param ID
     * @param passwd
     */
    void login(const QString &ID, const QString &passwd);

    void resetLogin();

    void refresh(const QString &ID);

    void sendAppDescription(const QString& name);

    void runApp(const QString& name);

    void sendNameList();


public:
    QWaitCondition waitCondition;

    explicit Core(const std::string &configPath);

    ~Core() override;
private:


    QMutex mutex;

    DatabaseSQLite db;

    ExtManager extManager;

    std::string workingDir;

    std::string databaseType;

    std::string databaseUrl;

    std::string extensionUrl;

    User user;

    PathManager pathManager;

    void configInit(const std::string &configPath);

    void dataBaseInit();

    void extManagerInit();

    void switchState(State state);

    User passwdCheck(const std::string &ID, const std::string &passwd);

    void lookUpUserInfo(const std::string &ID, char **&pData, int &rows, int &cols, double &score);


    void sendAppList();

};


#endif //ACPS_CORE_H
