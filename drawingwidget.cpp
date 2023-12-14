#include "drawingwidget.h"
#include <QApplication>
//#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPixmap>
#include <QWindow>

/*DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent) {
    //setMinimumSize(800, 600);
    showFullScreen();
    setWindowOpacity(0.1);

    drawing = false;

//    QPushButton *captureButton = new QPushButton("Capture and Process", this);
//    connect(captureButton, &QPushButton::clicked, this, &DrawingWidget::captureAndProcess);

//    // Make the button have a black background
//    captureButton->setStyleSheet("background-color: black; color: white;");
//    // Set the position and size of the button
//    captureButton->setGeometry(50, 50, 200, 30);  // Sample values, you can adjust according to your needs.

//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(captureButton);
//    layout->addWidget(this);

}*/

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_TranslucentBackground);  // Enable transparent background
    setAttribute(Qt::WA_NoSystemBackground, false);  // Disable system background
    setWindowFlags(Qt::FramelessWindowHint);  // Remove window frame

    drawing = false;

    // Capture the desktop's screenshot
    //QScreen *screen = QGuiApplication::primaryScreen();

    // Get the screen where the mouse is located
    QScreen *screen = QGuiApplication::screenAt(QCursor::pos());
    QPixmap desktopScreenshot = screen->grabWindow(0);
    desktopScreenshot.save("screenshot.png");

    // Set the desktop screenshot as the background
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(desktopScreenshot));
    setPalette(palette);

    showFullScreen();
    //setWindowOpacity(0.1);

}

void DrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap)); //black 2

    if (!path.isEmpty()) {
        painter.drawPath(path);
    }
}

void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        path.moveTo(event->pos());
        drawing = true;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        path.lineTo(event->pos());
        update();
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

void DrawingWidget::captureAndProcess() {
    QScreen *screen = QGuiApplication::primaryScreen();
    screenshot = screen->grabWindow(0);  // 0 represents the main window of the desktop
    update();

}
