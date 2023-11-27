#include "drawingwidget.h"
#include <QApplication>
//#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPixmap>
#include <QWindow>

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent) {
    //setMinimumSize(800, 600);
    showFullScreen();
    setWindowOpacity(0.1);

    drawing = false;

//    QPushButton *captureButton = new QPushButton("Capture and Process", this);
//    connect(captureButton, &QPushButton::clicked, this, &DrawingWidget::captureAndProcess);

//    // Butonu siyah arka planlı yapma
//    captureButton->setStyleSheet("background-color: black; color: white;");
//    // Butonun konumunu ve boyutunu ayarlama
//    captureButton->setGeometry(50, 50, 200, 30);  // Örnek değerler, ihtiyacınıza göre ayarlayabilirsiniz.

//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(captureButton);
//    layout->addWidget(this);

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
    screenshot = screen->grabWindow(0);  // 0, masaüstünün ana penceresini temsil eder
    update();

}
