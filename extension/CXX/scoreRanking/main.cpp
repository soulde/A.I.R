#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "MainWindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget* window = new MainWindow();
    window->show();
    return QApplication::exec();
}
