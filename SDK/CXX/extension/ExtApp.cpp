//
// Created by lyjly on 2022/2/26.
//

#include "ExtApp.h"



ExtApp::ExtApp(int argc, char **argv) : QApplication(argc, argv){
    if (QApplication::arguments().size() == 3) {
        QApplication::arguments()[2].toStdString();
    } else {
        QMessageBox::information(this, "错误的打开方式", "这是一个子程序，在管理系统中打开");
        exit(0);
    }
}
