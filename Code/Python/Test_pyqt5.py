#no need to install anything
import sys
# pip install pyqt5, pip install pyqt5 tools
from PyQt5.QtWidgets import QApplication, QMainWindow
# just change the name
from Test_PYUI import Ui_MainWindow

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        # the way app working
        self.uic = Ui_MainWindow()
        self.uic.setupUi(self)

if __name__ == "__main__":
    # run app
    app = QApplication(sys.argv)
    main_win = MainWindow()
    main_win.show()
    sys.exit(app.exec())