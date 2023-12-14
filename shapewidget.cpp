#include "shapewidget.h"
#include <QApplication>
#include <QMouseEvent>
#include <QPixmap>
#include <QWindow>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true); // Track mouse movements

    setAttribute(Qt::WA_TranslucentBackground);  // Enable transparent background
    setAttribute(Qt::WA_NoSystemBackground, false);  // Disable system background
    setWindowFlags(Qt::FramelessWindowHint);  // Remove window frame

    // Capture the desktop's screenshot
    //QScreen *screen = QGuiApplication::primaryScreen();

    // Get the screen where the mouse is located
    QScreen *screen = QGuiApplication::screenAt(QCursor::pos());
    QPixmap desktopScreenshot = screen->grabWindow(0);

    // Set the desktop screenshot as the background
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(desktopScreenshot));
    setPalette(palette);

    showFullScreen();
    //setWindowOpacity(0.1);
}

void ShapeWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Start drawing a new rectangle when the left mouse button is pressed
        currentRect = QRectF(event->pos(), QSize(0, 0));
        update(); // Trigger the paintEvent
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // Update the rectangle while the left mouse button is held down
        currentRect.setSize(QSize(event->pos().x() - currentRect.x(), event->pos().y() - currentRect.y()));
        update(); // Trigger the paintEvent
    }
}

void ShapeWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Finish drawing when the left mouse button is released
        rectangles.append(currentRect);
        currentRect = QRectF(); // Clear the current rectangle
        update(); // Trigger the paintEvent
    }
}

void ShapeWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));

    // Draw previously created rectangles
    for (const QRectF &rect : rectangles) {
        painter.drawRect(rect);
    }

    // Draw the currently being drawn rectangle
    if (!currentRect.isNull()) {
        painter.drawRect(currentRect);
    }
}
