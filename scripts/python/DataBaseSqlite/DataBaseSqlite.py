from sqlite3 import *
import pandas as pd


class DataBaseSqlite:
    def __init__(self, url):
        self.conn = connect(url)
        self.c = self.conn.cursor()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.conn.close()

    def get_data_table(self, cmd):
        return pd.read_sql_query(cmd, self.conn)

    def insert_batch(self, cmd, data_list):
        try:
            self.c.executemany(cmd, data_list)
            self.conn.commit()
        except Exception as e:
            self.conn.rollback()
            raise e

    def execute_cmd(self, cmd):
        try:
            self.c.execute(cmd)
            self.conn.commit()
        except Exception as e:
            self.conn.rollback()
            raise e
