from UI.ui_export_window import Ui_MainWindow
from PyQt5.Qt import Qt, QFileDialog, QMessageBox, QApplication

from FrameLessWindow import FrameLessWindow
from DataBaseSqlite.DataBaseSqlite import DataBaseSqlite as DB
import pandas as pd
import time, datetime


class MainWindow(FrameLessWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setWindowFlag(Qt.FramelessWindowHint, True)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.selectPathButton.clicked.connect(self.find_path)
        self.ui.exporButton.clicked.connect(self.export_data)
        self.db_url = QApplication.arguments()[2]

    def find_path(self):
        path = QFileDialog.getExistingDirectory(self, "选择导出位置", "C://")
        self.ui.pathLineEdit.setText(path)

    def export_sum(self, db):
        try:
            sql = "select names.ID as '学号', names.Name as '姓名',TechGroup as '技术组组别', AdminGroup as '管理部组别', sum([score record].Score)as '总分' from names join[score record] on names.ID=[score record].ID"
            group_by = " group by names.ID "
            main_table = db.get_data_table(sql + group_by + "order by 总分 desc")
            sub_sql = "select names.ID as '学号', sum([score record].Score)as '总分' from names join[score record] on names.ID=[score record].ID"
            positive_table = db.get_data_table(sub_sql + " where [score record].Score > 0" + group_by)
            negative_table = db.get_data_table(sub_sql + " where [score record].Score < 0" + group_by)

            positive_table.rename(columns={'总分': '加分总计'}, inplace=True)
            negative_table.rename(columns={'总分': '扣分总计'}, inplace=True)

            main_table = main_table.join(positive_table.set_index('学号'), on='学号')
            main_table = main_table.join(negative_table.set_index('学号'), on='学号')
            month = datetime.datetime.today().month + 1
            year = datetime.datetime.today().year
            for i in range(12):
                last_month = month - 1
                last_year = year
                if last_month == 0:
                    last_month = 12
                    year -= 1
                sql = sub_sql + " where [score record].Time >'" + str(year) + "/" + (
                    ("0" + str(last_month)) if len(str(last_month)) == 1 else str(
                        last_month)) + "/01' and [score record].Time <'" + str(last_year) + "/" + (
                          ("0" + str(month)) if len(str(month)) == 1 else str(month)) + "/01'" + group_by

                sub_table = db.get_data_table(sql)
                sub_table.rename(columns={'总分': str(year) + "年" + str(last_month) + "月"}, inplace=True)
                main_table = main_table.join(sub_table.set_index('学号'), on='学号')
                main_table = main_table.fillna("0")
                month = last_month

            return main_table
        except Exception as e:

            raise e

    def export_data(self):
        table_list = ['记录表', '成员表', '总表']

        with DB(self.db_url) as db:
            sql = self.analyse_filter(self.ui.tabWidget.currentIndex())
            df = pd.DataFrame()
            try:
                if self.ui.tabWidget.currentIndex() in [0, 1]:
                    df = db.get_data_table(sql)
                elif self.ui.tabWidget.currentIndex() == 2:
                    df = self.export_sum(db)

                if not df.empty:
                    df = df.fillna('')
                    df = df.applymap(str)

                    df.loc[:, '学号'] = df.loc[:, '学号'].map(lambda x: x[1:])
                else:
                    QMessageBox.warning(self, "warning", '空表')

                df.to_excel(
                    self.ui.pathLineEdit.text() + '/' + table_list[self.ui.tabWidget.currentIndex()] + time.strftime(
                        "%y-%m-%d", time.localtime()) + '导出.xlsx', index=False)
                QMessageBox.warning(self, "warning", '导出成功')
            except Exception as e:
                QMessageBox.warning(self, "warning", str(e))

    def analyse_filter(self, index):
        ret = ''
        if index == 0:
            ret = "select [Index] as '序号', names.ID as '学号',names.Name as '姓名', Score as '分数', Tips as '备注', Operator as '操作人', Time as '时间' from [score record] join names on [score record].ID == names.ID"
            if self.ui.dateCheckBox.isChecked():
                date_start = self.ui.startDateEdit.text().split('/')
                date_end = self.ui.endDateEdit.text().split('/')
                ret += " where Time >= '"
                for i in date_start:
                    ret += ("/0" + i) if len(i) == 1 else i
                ret += "' and Time <= '"
                for i in date_end:
                    ret += ("/0" + i) if len(i) == 1 else i
                ret += "'"
            if self.ui.groupCheckBox.isChecked():
                ret += " and names.TechGroup = '" + self.ui.groupComboBox.currentText() + "'"

        elif index == 1:
            ret = "select ID as '学号',Name as '姓名',Sex as '性别',School as '学院',Grade as '年级', TechGroup as '技术组组别', AdminGroup as '管理部组别', QQ as 'QQ号码', Tel as '手机号码' from names"
        return ret
