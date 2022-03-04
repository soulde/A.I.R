#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        FrameLessWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->enlargeButton, SIGNAL(clicked()), SLOT(zoomInAndOut()));
    connect(ui->rollbackButton, SIGNAL(clicked()), SLOT(sendRollbackSignal()));
    connect(ui->refreshButton, SIGNAL(clicked()), SLOT(sendRefreshSignal()));
    connect(ui->searchTableWidget, SIGNAL(itemClicked(QTableWidgetItem * )),
            SLOT(nameWidgetUpdate(QTableWidgetItem * )));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem * )), SLOT(listWidgetUpdate(QListWidgetItem * )));
    connect(ui->runAppButton, SIGNAL(clicked()), SLOT(sendRunAppSignal()));
    connect(ui->searchLineEdit, SIGNAL(textChanged(const QString &)), SLOT(searchSlot(const QString &)));

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::zoomInAndOut() {
    {
        static bool isMax;
        if (isMax) {
            this->showNormal();
            isMax = false;
        } else {
            this->showMaximized();
            isMax = true;
        }
    }
}

void MainWindow::userSetWindow(const QString &ID, const QString &name, bool isAdmin) {
    if (!isAdmin) {
        ui->tabWidget->setTabVisible(1, false);
        ui->searchTableWidget->setVisible(false);
        ui->searchLineEdit->setVisible(false);
    }
    ui->nameLabel->setText(name);

    currentSelectId = ID;
    ui->runAppButton->hide();

}

void MainWindow::userSetTable(char **pData, int rows, int cols, double score) {
    ui->lcdNumber->setProperty("value", QVariant(score));
    ui->recordTableWidget->setRowCount(rows);
    ui->recordTableWidget->setColumnCount(3);

    QString titles[] = {"时间", "分数", "备注"};
    QTableWidgetItem *item;
    for (int i = 0; i < 3; i++) {
        item = new QTableWidgetItem(titles[i]);
        ui->recordTableWidget->setHorizontalHeaderItem(i, item);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            item = new QTableWidgetItem(QString(pData[(i + 1) * cols + j]));
            ui->recordTableWidget->setItem(i, j, item);
        }
    }
}


void MainWindow::nameWidgetUpdate(QTableWidgetItem *item) {
    int row = item->row();
    if (ui->searchTableWidget->item(row, 0)->text() == ui->nameLabel->text()) {
        ui->userLabel->setText("你");
    } else {
        ui->userLabel->setText(ui->searchTableWidget->item(row, 0)->text());
    }
    currentSelectId = ui->searchTableWidget->item(row, 1)->text();
    sendRefreshSignal();

}

void MainWindow::listWidgetUpdate(QListWidgetItem *item) {
    if (!ui->runAppButton->isVisible()) {
        ui->runAppButton->setVisible(true);
    }
    emit requestDescriptionSignal(item->text());
}


void MainWindow::setSearchTableWidget(char **pUser, int userNum) {
    QTableWidgetItem *item;
    QStringList list;
    ui->searchTableWidget->setRowCount(userNum);
    ui->searchTableWidget->setColumnCount(2);
    for (int j = 0; j < userNum; j++) {
        item = new QTableWidgetItem;
        item->setText(QString(pUser[(j + 1) * 2]));
        ui->searchTableWidget->setItem(j, 0, item);
        item = new QTableWidgetItem;
        ui->searchTableWidget->setItem(j, 1, item);
        item->setText(QString(pUser[(j + 1) * 2 + 1] + 1));
        list.push_back(pUser[(j + 1) * 2]);
        list.push_back(pUser[(j + 1) * 2 + 1]);
    }

}

void MainWindow::setDescription(const QString &url) {
    ui->textBrowser->setSource(QUrl(QString("file:///") + url), QTextDocument::MarkdownResource);
}

void MainWindow::messageSlot(const QString &message) {
    QMessageBox::information(this, "", message);
}

void MainWindow::setAppList(const QList<QString> &appList) {
    ui->listWidget->addItems(appList);
}

void MainWindow::sendRunAppSignal() {
    emit runAppSignal(ui->listWidget->currentItem()->text());
}

void MainWindow::searchSlot(const QString &str) {

    QList<QTableWidgetItem *> items = ui->searchTableWidget->findItems(str, Qt::MatchContains);
    if (ui->searchLineEdit->text().isEmpty()) {
        for (int i = 0; i < ui->searchTableWidget->rowCount(); i++) {
            ui->searchTableWidget->setRowHidden(i, false);
        }
    } else {
        for (int i = 0; i < ui->searchTableWidget->rowCount(); i++) {
            ui->searchTableWidget->setRowHidden(i, true);
        }
        for (auto item : items) {
            ui->searchTableWidget->setRowHidden(item->row(), false);
        }
    }

}









