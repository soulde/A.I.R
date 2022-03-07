import os
import sys
from PyQt5.Qt import QApplication
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from UI.import_window import MainWindow


def main():
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
