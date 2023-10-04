#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <FrameLessWindow.h>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include "AddMemberForm.h"
#include "DatabaseSQLite.h"

namespace Ui {
    class AddMember;
}

class AddMember : public FrameLessWindow {
Q_OBJECT

public:
    explicit AddMember(QWidget *parent = nullptr);

    ~AddMember();


protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    bool bPressFlag;

    QPoint beginDrag;
private:
    Ui::AddMember *ui;

    QWidget *pForm = nullptr;

    DatabaseSQLite db;
    const std::map<std::string, std::string> nameMap = {{"学号", "name"},
                                                        {"姓名", "Name"},
                                                        {"性别", "Sex"},
                                                        {"学院",   "School"},
                                                        {"年级",   "Grade"},
                                                        {"技术组组别",   "TechGroup"},
                                                        {"管理部组别",   "AdminGroup"},
                                                        {"QQ号码",   "QQ"},
                                                        {"手机号码",   "Tel"},
                                                        {"密码", "Password"}};


private slots:

    void addItemSlot();

    void deleteSlot();

    void updateTable();

    void collectItem(QTableWidgetItem *Item);

    void refreshClickState();

    void updateItem(QTableWidgetItem *Item);

    void insertSlot(const QString &cmd);

private:
    static std::string ID;

    static bool dClicked;
};


#endif // ADDMEMBER_H
