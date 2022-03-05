from PyQt5.Qt import QMainWindow, Qt
from PyQt5 import QtGui


class FrameLessWindow(QMainWindow):
    def __init__(self, parent=None):
        super(QMainWindow, self).__init__(parent)
        self.setWindowFlag(Qt.FramelessWindowHint, True)

        self._pressed = False
        self._begin_drag = (0, 0)

    def mousePressEvent(self, a0: QtGui.QMouseEvent) -> None:
        self._pressed = True
        self._begin_drag = a0.globalPos() - self.pos()
        super(FrameLessWindow, self).mousePressEvent(a0)

    def mouseReleaseEvent(self, a0: QtGui.QMouseEvent) -> None:
        self._pressed = False
        super(FrameLessWindow, self).mouseReleaseEvent(a0)

    def mouseMoveEvent(self, a0: QtGui.QMouseEvent) -> None:
        if self._pressed:
            drift = a0.globalPos() - self._begin_drag
            self.move(drift)
        super(FrameLessWindow, self).mouseMoveEvent(a0)