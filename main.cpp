#include "mainwindow.h"
#include "drawingwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setStyleSheet(//"QButton{background: #000000; border-radius: 10px; font-family: Gilroy; font-size: 20px; color: white;}"
                    "QMainWindow{font-family: Gilroy; font-size: 14px; font-weight: Normal; background: rgba(36,36,36,100%); border-radius: 30px;}"
                    "QAbstractButton {background: #000000; font-size: 20px; border-radius: 5px; color: white; font-family: Gilroy;}"
                    "QAbstractButton:pressed, QAbstractButton:checked {background: #414141; font-size: 20px; border-radius: 5px; color: white; font-family: Gilroy;}");
    w.show();

    //DrawingWidget widget;
    //widget.show();


    return a.exec();
}
