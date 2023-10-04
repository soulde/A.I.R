#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMessageBox>
#include "User.h"

namespace Ui {
    class AddMemberForm;
}

class AddMemberForm : public QWidget {
Q_OBJECT

signals:
    void addSignal(const QString& str);
public:
    explicit AddMemberForm(QWidget *parent = nullptr);

    ~AddMemberForm();

private slots:
    void addConfirm();

private:
    Ui::AddMemberForm *ui;

};

#endif // FORM_H
