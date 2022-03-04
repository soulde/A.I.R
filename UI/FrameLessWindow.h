//
// Created by lyjly on 2022/2/26.
//

#ifndef AIR_FRAMELESSWINDOW_H
#define AIR_FRAMELESSWINDOW_H


#include <QMainWindow>
#include <QMouseEvent>

class FrameLessWindow : public QMainWindow{
Q_OBJECT
public:
    explicit FrameLessWindow(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool bPressFlag;

    QPoint beginDrag;
};


#endif //AIR_FRAMELESSWINDOW_H
