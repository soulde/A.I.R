#ifndef ADDSCORE_H
#define ADDSCORE_H

#include <FrameLessWindow.h>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include <QMessageBox>
#include "DatabaseSQLite.h"
#include "AddScoreForm.h"

namespace Ui {
class AddScore;
}

class AddScore : public FrameLessWindow
{
    Q_OBJECT

public:
    explicit AddScore(QWidget *parent = nullptr);
    ~AddScore();
signals:
    void listSignal(const QStringList&);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool bPressFlag;

    QPoint beginDrag;
private:
    Ui::AddScore *ui;

    QWidget* pForm = nullptr;

    DatabaseSQLite db;

    QString userID;

    int getIndex();
public slots:
    void addScore(const QString &ID, const QString& Des, double score);

    void delRecord();

private slots:
    void addScoreSlot();


};

#endif // ADDSCORE_H
