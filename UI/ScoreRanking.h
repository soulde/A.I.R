#ifndef SCORERANKING_H
#define SCORERANKING_H

#include <FrameLessWindow.h>
#include <QTableWidgetItem>
#include <QMouseEvent>

#include "DatabaseSQLite.h"

namespace Ui {
    class ScoreRanking;
}

class ScoreRanking : public FrameLessWindow {
Q_OBJECT

public:
    explicit ScoreRanking(QWidget *parent = nullptr);

    ~ScoreRanking();


protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    bool bPressFlag;

    QPoint beginDrag;
private:
    void updateTable();

    Ui::ScoreRanking *ui;

    QWidget *pForm = nullptr;

    DatabaseSQLite db;

};


#endif // SCORERANKING_H
