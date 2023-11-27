#include "mainwindow.h"
#include "drawingwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //DrawingWidget widget;
    //widget.show();

    return a.exec();
}
