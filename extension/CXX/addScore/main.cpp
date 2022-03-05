#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString arg;



    QWidget* window = new MainWindow();
    window->show();
    return QApplication::exec();
}
