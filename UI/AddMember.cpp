
#include "AddMember.h"
#include "ui_AddMember.h"
#include "yaml-cpp/yaml.h"

std::string AddMember::ID = "";
bool AddMember::dClicked = false;


AddMember::AddMember(QWidget *parent) :
        FrameLessWindow(parent),
        ui(new Ui::AddMember) {
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
    connect(ui->nameTableWidget, SIGNAL(itemClicked(QTableWidgetItem * )), this, SLOT(refreshClickState()));
    connect(ui->nameTableWidget, SIGNAL(itemChanged(QTableWidgetItem * )), this, SLOT(updateItem(QTableWidgetItem * )));

}

void AddMember::updateTable() {
    Table table{};

    table.getTable(
            "select ID as '学号', Name as '姓名', Sex as '性别',School as '学院', Grade as '年级', TechGroup as '技术组组别', AdminGroup as '管理部组别', QQ as 'QQ号码', Tel as '手机号码', Password as '密码' from [names]",
            db);
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
            item = new QTableWidgetItem(QString(pT[(i + 1) * cols + j] + ((j == 0 || j == cols - 1) ? 1 : 0)));
            ui->nameTableWidget->setItem(i, j, item);

        }
    }
}

void AddMember::addItemSlot() {
    pForm = new AddMemberForm();
    connect(pForm, SIGNAL(addSignal(const QString&)), this, SLOT(insertSlot(const QString&)));
    pForm->show();
}

void AddMember::insertSlot(const QString &cmd) {
    db.executeCmd(cmd.toStdString());
    updateTable();
}

void AddMember::collectItem(QTableWidgetItem *Item) {
    QTableWidgetItem *temp = ui->nameTableWidget->item(Item->row(), 0);
    ID = temp->text().toStdString();
    dClicked = true;
}

void AddMember::refreshClickState() {
    dClicked = false;
}

void AddMember::updateItem(QTableWidgetItem *Item) {
    if (dClicked) {
        QTableWidgetItem *header = ui->nameTableWidget->horizontalHeaderItem(Item->column());
        std::string upStr =
                "update names set " + nameMap.at(header->text().toStdString()) + "='" +
                ((Item->column() == ui->nameTableWidget->columnCount() - 1) ? "_" : "") + Item->text().toStdString() +
                "' where ID = '_" +
                ID + "'";

        db.executeCmd(upStr);
    }
}

void AddMember::deleteSlot() {
    QTableWidgetItem *temp = ui->nameTableWidget->item(ui->nameTableWidget->currentRow(), 0);
    if (!temp->text().isEmpty()) {
        std::string delStr = "delete from names where ID = '_" + temp->text().toStdString() + "'";
        db.executeCmd(delStr);
    }

    updateTable();
}

AddMember::~AddMember() {

    delete ui;
}

void AddMember::mousePressEvent(QMouseEvent *event) {
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void AddMember::mouseReleaseEvent(QMouseEvent *event) {
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void AddMember::mouseMoveEvent(QMouseEvent *event) {
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}




