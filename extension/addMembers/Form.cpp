#include <iostream>
#include "Form.h"
#include "ui_Form.h"
#include "../addScore/Form.h"


Form::Form(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Form) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(addConfirm()));
    for (const auto &item:User::techGroup) {
        ui->techGroupComboBox->addItem(QString(item.c_str()));
    }
    for (const auto &item:User::adminGroup) {
        ui->adminGroupComboBox->addItem(QString(item.c_str()));
    }
    for (const auto &item:User::grade) {
        ui->adminComboBox->addItem(QString(item.c_str()));
    }
}

Form::~Form() {
    delete ui;
}




void Form::addConfirm() {

    std::string ID = ui->IDLineEdit->text().toStdString();
    std::string Name = ui->NameLineEdit->text().toStdString();
    std::string Tel = ui->TelLineEdit->text().toStdString();
    std::string Mail = ui->mailLineEdit->text().toStdString();
    std::string PassWord = ui->passwdLineEdit->text().toStdString();
    std::string Sex;
    if (ui->sexComboBox->currentIndex() == 0) {
        Sex = "male";
    } else {
        Sex = "female";
    }

    int index = ui->techGroupComboBox->currentIndex()*100 + ui->adminGroupComboBox->currentIndex()*10 + ui->adminComboBox->currentIndex();


    std::string insertCmd =
            "insert into names values('" + ID + "','" + Name + "','" + PassWord + "','" + Tel + "','" + Mail + "','" +
            Sex + "'," + std::to_string(index) + ")";

    emit addSignal(QString(insertCmd.c_str()));
    this->close();
}