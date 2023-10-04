#include <iostream>
#include "AddMemberForm.h"
#include "ui_AddMemberForm.h"


AddMemberForm::AddMemberForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::AddMemberForm) {
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
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    int year = ltm->tm_year + 1900;
    int month = ltm->tm_mon + 1;
    if (month < 7) {
        year -= 1;
    }
    for (int i = 0; i < 6; i++) {
        ui->gradeComboBox->addItem(QString(std::to_string(year - i).c_str()));
    }

}

AddMemberForm::~AddMemberForm() {
    delete ui;
}


void AddMemberForm::addConfirm() {

    std::string ID = ui->IDLineEdit->text().toStdString();
    std::string Name = ui->NameLineEdit->text().toStdString();
    std::string School = ui->schoolComboBox->currentText().toStdString();
    std::string Grade = ui->gradeComboBox->currentText().toStdString();
    std::string TechGroup = ui->techGroupComboBox->currentText().toStdString();
    std::string AdminGroup = ui->adminGroupComboBox->currentText().toStdString();
    std::string QQ = ui->QQLineEdit->text().toStdString();
    std::string Tel = ui->TelLineEdit->text().toStdString();
    std::string Sex = ui->sexComboBox->currentText().toStdString();


    std::string insertCmd =
            "insert into names (ID, Name, School, Grade, TechGroup, AdminGroup, QQ, Tel, Sex, Password) values('_" + ID + "','" +
            Name + "','" + School + "','" + Grade + "','" + TechGroup + "','" + AdminGroup + "','" + QQ + "','" + Tel +
            "','" + Sex + "','_')";

    emit addSignal(QString(insertCmd.c_str()));
    this->close();
}
