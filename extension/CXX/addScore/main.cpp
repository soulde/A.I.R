#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
#include <QWidget>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget* window = new MainWindow();
    window->show();
    return QApplication::exec();
}
