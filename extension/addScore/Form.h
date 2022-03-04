#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
    class Form;
}

class Form : public QWidget {
Q_OBJECT
signals:

    void addScoreSignal(const QString &, const QString &, double);


public:
     explicit Form(QWidget *parent = nullptr);

    ~Form();

public slots:

    void sendAddScoreSignal();

    void setComplete(const QStringList& list);

private:
    Ui::Form *ui;
};

#endif // FORM_H
