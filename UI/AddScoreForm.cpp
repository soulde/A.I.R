#include "AddScoreForm.h"
#include "ui_AddScoreForm.h"
#include <QMessageBox>
AddScoreForm::AddScoreForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::AddScoreForm) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->confirmPushButton, SIGNAL(clicked()), this, SLOT(sendAddScoreSignal()));

}

void AddScoreForm::setComplete(const QStringList& list) {
    auto* completer = new QCompleter(list);
    completer->setFilterMode(Qt::MatchContains);
    ui->IDLineEdit->setCompleter(completer);
}
void AddScoreForm::sendAddScoreSignal() {
    QString ID = ui->IDLineEdit->text();
    QString Des = ui->DesLineEdit->text();
    double score = ui->scoreSpinBox->value();
    if (ui->comboBox->currentIndex() != 0) {
        score *= -1;
    }

    emit addScoreSignal(ID, Des, score);
    close();
}

AddScoreForm::~AddScoreForm() {
    delete ui;
}
