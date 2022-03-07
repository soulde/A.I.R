
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "yaml-cpp/yaml.h"
#include "../addMembers/MainWindow.h"

#include <utility>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    if (QApplication::arguments().size() == 3) {
        db = DatabaseSQLite(QApplication::arguments()[2].toStdString());
        userID = QApplication::arguments()[1];
    } else {
        QMessageBox::information(this, "错误的打开方式", "这是一个子程序，在管理系统中打开");
        exit(0);
    }

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->addPushButton, SIGNAL(clicked()), this, SLOT(addScoreSlot()));
    connect(ui->rollBackPushButton, SIGNAL(clicked()), SLOT(delRecord()));
}

void MainWindow::addScoreSlot() {
    Query q;
    QStringList list;
    q.prepareCmd("select ID from names", db);
    while (q.read()) {
        auto item = q.getData<std::string>(0);
        list.push_back(QString(item.c_str()));
    }
    pForm = new Form();
    pForm->show();
    connect(pForm, SIGNAL(addScoreSignal(const QString &, const QString &, double)),
            SLOT(addScore(const QString &, const QString &, double)));
    connect(this, SIGNAL(listSignal(const QStringList &)), pForm, SLOT(setComplete(const QStringList& )));
    emit listSignal(list);
}


MainWindow::~MainWindow() {
    pForm->close();
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


void MainWindow::addScore(const QString &ID, const QString &Des, double score) {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    std::string date =
            std::to_string(ltm->tm_year + 1900) + "/" + std::to_string(ltm->tm_mon + 1) + "/" +
            std::to_string(ltm->tm_mday);


    int index = getIndex() + 1;

    std::string addScoreCmd =
            "insert into [score record] values(" + std::to_string(index) + ",'_" + ID.toStdString() + "'," +
            std::to_string(score) + ",'" +
            Des.toStdString() + "','" + userID.toStdString() + "','" + date + "')";

    db.executeCmd(addScoreCmd);
    auto *IDItem = new QTableWidgetItem(ID);
    auto *scoreItem = new QTableWidgetItem(QString(std::to_string(score).c_str()));

    int row = ui->nameTableWidget->rowCount();
    ui->nameTableWidget->setRowCount(row + 1);
    ui->nameTableWidget->setItem(row, 0, IDItem);
    ui->nameTableWidget->setItem(row, 1, scoreItem);
}

void MainWindow::delRecord() {
    QTableWidgetItem *temp = ui->nameTableWidget->item(ui->nameTableWidget->currentRow(), 0);
    if (!temp->text().isEmpty()) {
        std::string delStr = "delete from [score record] where ID = '" + temp->text().toStdString() + "'";
        db.executeCmd(delStr);
    }

    ui->nameTableWidget->removeRow(ui->nameTableWidget->currentRow());
    ui->nameTableWidget->setRowCount(ui->nameTableWidget->rowCount() - 1);

}

int MainWindow::getIndex() {
    Query q;
    q.prepareCmd("select count(*) from [score record]", db);
    q.read();
    return q.getData<int>(0);
}
