from PyQt5.Qt import QApplication
import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from UI.import_window import MainWindow


def main():
    myapp = QApplication(sys.argv)

    window = MainWindow()
    window.show()
    sys.exit(myapp.exec_())


if __name__ == '__main__':
    main()
