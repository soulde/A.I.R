#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include "Form.h"
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
    Ui::MainWindow *ui;

    QWidget* pForm = nullptr;

    DatabaseSQLite db;


private slots:
    void addItemSlot();

    void deleteSlot();

    void updateTable();

    void collectItem( QTableWidgetItem * Item);

    void refreshClickState();

    void updateItem( QTableWidgetItem * Item);

    void insertSlot(const QString& cmd);

private:
    static std::string ID;

    static bool dClicked;
};


#endif // MAINWINDOW_H
