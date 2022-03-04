#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "FrameLessWindow.h"


namespace Ui {
    class LoginWindow;
}

class LoginWindow : public FrameLessWindow {
Q_OBJECT

signals:

    void loginSignal(const QString&, const QString&);



private slots:

    void login();

    void messageSlot(const QString& message);
public:

    explicit LoginWindow(QWidget *parent = nullptr);


    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

};

#endif // LOGINWINDOW_H
