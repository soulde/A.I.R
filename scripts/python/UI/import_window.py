import time

from ui_import_window import Ui_MainWindow
from PyQt5.Qt import QFileDialog, QMessageBox

import pandas as pd
from FrameLessWindow import FrameLessWindow
from DataBaseSqlite.DataBaseSqlite import DataBaseSqlite as DB


class MainWindow(FrameLessWindow):
    def __init__(self, user_id, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.selectPathButton.clicked.connect(self.find_path)
        self.ui.confirmButton.clicked.connect(self.data_import)
        self.id = user_id
        self.db_url = 'E:\Documents\project\AIR\data\AIR.db'

    def find_path(self):
        path = QFileDialog.getOpenFileName(self, "选择导入的表格", "C://")[0]
        self.ui.pathLineEdit.setText(path)

    def data_import(self):
        msg = '确认将表格数据导入 ' + ('人员信息表' if self.ui.memberButton.isChecked() else '加分信息表') + '?'
        if QMessageBox.No == QMessageBox.question(self, '确认', msg, QMessageBox.Yes | QMessageBox.No, QMessageBox.No):
            return

        try:
            df = pd.read_excel(self.ui.pathLineEdit.text(), converters={0: str})
            with DB(self.db_url) as db:
                if self.ui.memberButton.isChecked():
                    self._import_member(df, db)
                    QMessageBox.information(self, '导入成功', '数据已成功导入成员信息表')

                elif self.ui.scoreButton.isChecked():
                    self._import_record(df, db)
                    QMessageBox.information(self, '导入成功', '数据已成功导入加分信息表')

        except Exception as e:
            QMessageBox.warning(self, 'warning', '无法导入表格： ' + str(e))

    def _import_member(self, df, db):
        sql = 'insert into names (ID, Name, school, Grade,TechGroup, AdminGroup, QQ, Tel) values (?,?, ?, ?, ?, ?, ?, ?);'
        if df.columns.tolist() != ['学号', '姓名', '学院', '年级', '技术组组别', '管理部组别', 'QQ号码', '手机号码']:
            print(df.columns.tolist())
            raise Exception('表格格式错误，请使用正确模板, 按(学号, 姓名, 学院, 年级, 技术组组别, 管理部组别, QQ号码, 手机号码)排列')

        old_df = db.get_data_table("select ID as '学号', Name as '姓名', School as '学院', Grade as '年级', TechGroup as '技术组组别', AdminGroup as '管理部组别', QQ as 'QQ号码', Tel as '手机号码' from names")
        df = df.fillna('')
        df.iloc[:, 0] = df.iloc[:, 0].map(lambda x: "_" + x)
        old_df = old_df.applymap(str)

        df = pd.concat([df, old_df])
        df.drop_duplicates(df.columns[0], 'first', True)
        print(df)
        data = df.values.tolist()
        data = list(map(lambda x: tuple(x), data))
        print(data)
        db.execute_cmd('delete from names')
        db.insert_batch(sql, data)

    def _import_record(self, df, db):
        if df.columns.tolist() != ['学号', '姓名', '技术组组别', '管理部组别', '分值', '备注']:
            print(df.columns.tolist())
            raise Exception('表格格式错误，请使用正确模板, 按(学号, 姓名, 技术组组别, 管理部组别, 分值, 备注)排列')
        t = db.get_data_table('select count(*) from [score record]')
        start = t.iloc[0, 0] + 1

        sql = 'insert into [score record] (ID, score, Tips, Operator, Time ,[Index]) values (?, ?, ?, ?, ?, ?);'
        df = df.fillna('')
        df = df.iloc[:, [0, 4, 5]]
        data = df.values.tolist()

        data_list = []
        for i, item in enumerate(data[:]):
            item[0] = "_" + item[0]
            item.extend([self.id, time.strftime("%Y/%m/%d", time.localtime()), str(i + start)])
            data_list.append(tuple(item))

        db.insert_batch(sql, data_list)
