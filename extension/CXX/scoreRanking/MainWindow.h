#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMouseEvent>

#include "DatabaseSQLite.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool bPressFlag;

    QPoint beginDrag;
private:
    void updateTable();
    Ui::MainWindow *ui;

    QWidget* pForm = nullptr;

    DatabaseSQLite db;

};


#endif // MAINWINDOW_H
