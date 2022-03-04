#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QtWidgets>
#include "FrameLessWindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public FrameLessWindow {
Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


signals:
    void rollbackSignal();

    void refreshSignal(QString ID);

    void requestDescriptionSignal(const QString& name);

    void runAppSignal(const QString& name);

public slots:

    void userSetWindow(const QString& ID, const QString& name, bool isAdmin);
    void userSetTable(char **pData, int rows, int cols, double score);
    void setSearchTableWidget(char**pUser, int userNum);

    void nameWidgetUpdate(QTableWidgetItem *item);

    void listWidgetUpdate(QListWidgetItem* item);

    void setAppList(const QList<QString>&appList);

    void setDescription(const QString& url);

    void messageSlot(const QString& message);

private slots:

    void zoomInAndOut();

    inline void sendRollbackSignal(){
        emit rollbackSignal();
    }

    inline void sendRefreshSignal(){
        emit refreshSignal(currentSelectId);
    }

    void searchSlot(const QString &str);
    void sendRunAppSignal();

private:
    QString currentSelectId;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
