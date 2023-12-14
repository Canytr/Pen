#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>
#include <QLabel>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Keep the window always on top
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    // Hide the title bar
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    // Enable events for dragging the window by holding the title bar
    //setMouseTracking(true);
    ui->centralwidget->installEventFilter(this);
    //installEventFilter(this);

    // Keep the window size fixed
    //setFixedSize(160, 400);

    QLabel *clockLabel = new QLabel(this);

    // Set the text color to white and make it bold
    clockLabel->setStyleSheet("QLabel { color : white; font-weight: bold; background-color: transparent; border: none; }");
    clockLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar()->addWidget(clockLabel);

    // Start Timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateClock);
    timer->start(1000); // Update every 1000 milliseconds (1 second)

    // Perform the initial update
    updateClock();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClock()
{
    // Get the current time
    QDateTime currentTime = QDateTime::currentDateTime();

    // Format the time and set it to a QLabel
    QString formattedTime = currentTime.toString("hh:mm:ss");
    statusBar()->findChild<QLabel*>()->setText(formattedTime);
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
    shapeWidget->close();
}

void MainWindow::on_pushButtonShape_clicked()
{
    shapeWidget = new ShapeWidget();
    shapeWidget->show();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Start the dragging operation
        isDragging = true;
        dragStart = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        // If the dragging operation is ongoing, move the QMainWindow
        move(event->globalPos() - dragStart);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Terminate the dragging operation
        isDragging = false;
        event->accept();
    }
}

void MainWindow::on_pushButtonQuit_clicked()
{
    QApplication::quit();
}



