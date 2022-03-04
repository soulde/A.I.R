#include "LoginWindow.h"
#include "ui_LoginWindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
        FrameLessWindow(parent),
        ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    connect(this->ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));

}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::login() {
    emit loginSignal(ui->lineEdit->text(), ui->lineEdit_2->text());
}



void LoginWindow::messageSlot(const QString &message) {
    QMessageBox::information(this, "", message);
}



