#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Pencereyi her zaman üstte tutma
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    // Başlık çubuğunu gizleme
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    // Başlık çubuğunu tutarak pencereyi sürüklemek için gereken olayları etkinleştir
    //setMouseTracking(true);
    ui->centralwidget->installEventFilter(this);
    //installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonPen_clicked()
{
    //DrawingWidget widget;
    widget = new DrawingWidget();
    widget->show();
}


void MainWindow::on_pushButtonPenDuster_clicked()
{
    widget->close();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Sürükleme işlemini başlat
        isDragging = true;
        dragStart = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        // Sürükleme işlemi devam ediyorsa QMainWindow'ı hareket ettir
        move(event->globalPos() - dragStart);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Sürükleme işlemini sonlandır
        isDragging = false;
        event->accept();
    }
}

void MainWindow::on_pushButtonQuit_clicked()
{
    QApplication::quit();
}

