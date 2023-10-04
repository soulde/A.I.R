#ifndef ADDSCOREFORM_H
#define ADDSCOREFORM_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
    class AddScoreForm;
}

class AddScoreForm : public QWidget {
Q_OBJECT
signals:

    void addScoreSignal(const QString &, const QString &, double);


public:
     explicit AddScoreForm(QWidget *parent = nullptr);

    ~AddScoreForm();

public slots:

    void sendAddScoreSignal();

    void setComplete(const QStringList& list);

private:
    Ui::AddScoreForm *ui;
};

#endif // ADDSCOREFORM_H
