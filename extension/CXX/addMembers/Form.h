#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMessageBox>
#include "User.h"

namespace Ui {
    class Form;
}

class Form : public QWidget {
Q_OBJECT

signals:
    void addSignal(const QString& str);
public:
    explicit Form(QWidget *parent = nullptr);

    ~Form();

private slots:
    void addConfirm();

private:
    Ui::Form *ui;

};

#endif // FORM_H
