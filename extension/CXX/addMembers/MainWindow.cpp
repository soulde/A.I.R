
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "yaml-cpp/yaml.h"

std::string MainWindow::ID = "";
bool MainWindow::dClicked = false;


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
    connect(ui->addPushButton, SIGNAL(clicked()), this, SLOT(addItemSlot()));
    connect(ui->delPushButton, SIGNAL(clicked()), this, SLOT(deleteSlot()));
    connect(ui->nameTableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem * )),
            this, SLOT(collectItem(QTableWidgetItem * )));
    connect(ui->nameTableWidget, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(refreshClickState()));
    connect(ui->nameTableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(updateItem(QTableWidgetItem *)));
}

void MainWindow::updateTable() {
    Table table{};
    table.getTable("select * from names", db);
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
            item = new QTableWidgetItem(QString(pT[(i + 1) * cols + j]));
            ui->nameTableWidget->setItem(i, j, item);

        }
    }
}

void MainWindow::addItemSlot() {
    pForm = new Form();
    connect(pForm, SIGNAL(addSignal(const QString&)), this, SLOT(insertSlot(const QString&)));
    pForm->show();
}

void MainWindow::insertSlot(const QString &cmd) {
    db.excuteCmd(cmd.toStdString());
    updateTable();
}

void MainWindow::collectItem(QTableWidgetItem *Item) {
    QTableWidgetItem *temp = ui->nameTableWidget->item(Item->row(), 0);
    ID = temp->text().toStdString();
    dClicked = true;
}

void MainWindow::refreshClickState() {
    dClicked = false;
}

void MainWindow::updateItem(QTableWidgetItem *Item) {
    if(dClicked){
        QTableWidgetItem *header = ui->nameTableWidget->horizontalHeaderItem(Item->column());
        std::string upStr =
                "update names set " + header->text().toStdString() + "='" + Item->text().toStdString() + "' where ID = '" +
                ID + "'";
        QMessageBox::information(this, "", QString(upStr.c_str()));
        db.excuteCmd(upStr);
    }
}

void MainWindow::deleteSlot() {
    QTableWidgetItem *temp = ui->nameTableWidget->item(ui->nameTableWidget->currentRow(), 0);
    if(!temp->text().isEmpty()){
        std::string delStr = "delete from names where ID = '" + temp->text().toStdString() + "'";
        db.excuteCmd(delStr);
    }

    updateTable();
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




