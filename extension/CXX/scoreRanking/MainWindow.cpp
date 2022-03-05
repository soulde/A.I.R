
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "yaml-cpp/yaml.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    if (QApplication::arguments().size() == 3) {
        db = DatabaseSQLite(QApplication::arguments()[2].toStdString());
    } else {
        QMessageBox::information(this, "错误的打开方式", "这是一个子程序，在管理系统中打开");
        exit(0);
    }
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    updateTable();

}

void MainWindow::updateTable() {
    Table table{};
    table.getTable("select * from [names]", db);
    char **pT;
    int rows, cols;
    table.getSrc(pT, cols, rows);
    ui->nameTableWidget->clear();
    ui->nameTableWidget->setRowCount(rows);
    ui->nameTableWidget->setColumnCount(cols);
    QStringList titles;
    QTableWidgetItem *item;
    for (int i = 0; i < cols; i++) {
        item = new QTableWidgetItem(QString(pT[i]));
        ui->nameTableWidget->setHorizontalHeaderItem(i, item);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            item = new QTableWidgetItem(QString(pT[(i + 1) * cols + j] + (j == 0 ? 1 : 0)));
            ui->nameTableWidget->setItem(i, j, item);

        }
    }
}


MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}




