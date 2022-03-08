//
// Created by lyjly on 2022/2/7.
//

#include "Core.h"
#include <QMessageBox>

Core::Core(const std::string &configPath) : QObject(), pathManager(configPath) {
    configInit(configPath);
    dataBaseInit();
    extManagerInit();
}

Core::~Core() {

}


void Core::login(const QString &ID, const QString &passwd) {
    user = passwdCheck(ID.toStdString(), passwd.toStdString());
    if (user.ID.empty()) {
        return;
    }
    alternate(MAIN);

    refresh(ID);
    emit userAccessSignal(ID, QString(user.name.c_str()), user.type);
    if (user.type) {
        sendNameList();
        sendAppList();
    }


}

void Core::resetLogin() {
    alternate(LOGIN);
}

void Core::refresh(const QString &ID) {
    char **pTable;
    int nRow, nCol;
    double sumScore;
    lookUpUserInfo(ID.toStdString(), pTable, nRow, nCol, sumScore);

    emit recordTableSignal(pTable, nRow, nCol, sumScore);

}

void Core::alternate(int windowType) {
    mutex.lock();
    emit alterWindowSignal(windowType);
    waitCondition.wait(&mutex);
    mutex.unlock();
}


void Core::configInit(const std::string &configPath) {
    YAML::Node config;

    try {
        config = YAML::LoadFile(configPath);
    } catch (YAML::BadFile &e) {
       emit messageSignal("找不到配置文件");
//        exit(0);
    }

    char *str;
    str = getcwd(nullptr, 0);
    std::string root = std::string(str);
    free(str);

    extensionUrl = PathManager::getValue("extensionDir");

}


void Core::dataBaseInit() {
    db = DatabaseSQLite(PathManager::getValue("databaseUrl"));
}

void Core::extManagerInit() {
    extManager = ExtManager(extensionUrl);
}


User Core::passwdCheck(const std::string &ID, const std::string &passwd) {
    User user;
    const std::string loginStr = "select Password, name from names where ID = @ID";
    Query query;

    query.prepareCmd(loginStr, db);
    query.bind<std::string>("_" + ID, 1);
    query.read();
    if (ID.empty()) {
        emit messageSignal(QString("请输入学号"));
        return User();
    }
    auto pw = query.getData<std::string>(0).substr(1);
    auto name = query.getData<std::string>(1);
    if (passwd.empty()) {
        user.type = User::user;
    } else {
        if (name.empty() || passwd != pw) {
            emit messageSignal(QString("学号或密码错误！！"));
            return User();
        } else {
            user.type = User::admin;
        }
    }

    user.ID = ID;
    user.name = name;

    return user;
}

void Core::lookUpUserInfo(const std::string &ID, char **&pData, int &rows, int &cols, double &score) {
    Query query;
    std::string countStr = "select sum(Score) from [score record] where ID = '_" + ID + "'";

    std::string err = query.prepareCmd(countStr, db);

    query.read();
    score = query.getData<double>(0);
    static Table table;

    std::string recordSelectStr = "select Time, Score,Tips from [score record] where ID = '_" + ID + "'";

    table.getTable(recordSelectStr, db);

    table.getSrc(pData, cols, rows);

}

void Core::sendNameList() {
    static Table t;
    char **p;
    int nRow, nCol;

    t.getTable("select Name, ID from names", db);
    t.getSrc(p, nCol, nRow);

    emit nameWidgetSignal(p, nRow);
}

void Core::sendAppList() {
    std::vector<std::string> appList;
    extManager.getAppList(appList);
    QList<QString> list;
    for (const auto &item:appList) {
        list.push_back(QString(item.c_str()));
    }
    emit listWidgetSignal(list);
}

void Core::sendAppDescription(const QString &name) {

    std::string description = extManager.getDescription(name.toStdString());
    emit appDescriptionSignal(QString(description.c_str()));
}

void Core::runApp(const QString &name) {
    std::string err = extManager.runApp(name.toStdString(), user.ID);
    if(!err.empty()){
        emit messageSignal(QString(err.c_str()));
    }

}














