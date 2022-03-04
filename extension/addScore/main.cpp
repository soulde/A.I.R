#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString arg;
    if(QApplication::arguments().size() == 1){
        arg = "";
    }else{
        arg = QApplication::arguments().at(1);
    }


    QWidget* window = new MainWindow(arg);
    window->show();
    return QApplication::exec();
}
