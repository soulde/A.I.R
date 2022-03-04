#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include <QMessageBox>
#include "DatabaseSQLite.h"
#include "Form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString ID, QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void listSignal(const QStringList&);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool bPressFlag;

    QPoint beginDrag;
private:
    Ui::MainWindow *ui;

    QWidget* pForm = nullptr;

    DatabaseSQLite db;

    QString userID;

    int getIndex();
public slots:
    void addScore(const QString &ID, const QString& Des, double score);

    void delRecord();

private slots:
    void addScoreSlot();


};

#endif // MAINWINDOW_H
