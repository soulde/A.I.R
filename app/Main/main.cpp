#include "Application.h"
#include <QApplication>
#include <QThread>
int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    //TODO: create a class "app" to contain the gui pointer and core alternate function become a signal and slot;
    Application app("../data/config.air");

    int ret =  QApplication::exec();

    return ret;
}