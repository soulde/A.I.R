//
// Created by lyjly on 2022/2/26.
//

#include "FrameLessWindow.h"

FrameLessWindow::FrameLessWindow(QWidget *parent) : QMainWindow(parent){
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

void FrameLessWindow::mousePressEvent(QMouseEvent *event) {
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void FrameLessWindow::mouseReleaseEvent(QMouseEvent *event) {
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void FrameLessWindow::mouseMoveEvent(QMouseEvent *event) {
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}