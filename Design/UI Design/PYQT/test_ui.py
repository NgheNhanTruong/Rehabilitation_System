import sys
# pip install pyqt5, pip install pyqt5 tools
from PyQt5.QtWidgets import QApplication, QMainWindow
# just change the name
from PYQT_RS import Ui_MainWindow

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        # the way app working
        self.uic = Ui_MainWindow()
        self.uic.setupUi(self)
        #define for button
        self.uic.Button_start.clicked.connect(self.show_page_2)
        self.uic.back_button.clicked.connect(self.show_page_1)

    def show_page_1(self):
        self.uic.stackedWidget.setCurrentWidget(self.uic.page_1)    
    def show_page_2(self):
        self.uic.stackedWidget.setCurrentWidget(self.uic.page_2)
if __name__ == "__main__":
    # run app
    app = QApplication(sys.argv)
    main_win = MainWindow()
    main_win.show()
    sys.exit(app.exec())
