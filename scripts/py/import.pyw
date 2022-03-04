import os
import sys
from PyQt5.Qt import QApplication
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


from import_window import *


def main():
    app = QApplication(sys.argv)
    window = MainWindow("李雨璟")
    window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
