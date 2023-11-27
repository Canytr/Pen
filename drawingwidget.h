#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QPainterPath>

class DrawingWidget : public QWidget {
    Q_OBJECT

public:
    DrawingWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void captureAndProcess();

private:
    bool drawing;
    QPainterPath path;
    QPixmap screenshot;
};

#endif // DRAWINGWIDGET_H
