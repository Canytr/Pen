#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "drawingwidget.h"
#include <shapewidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateClock();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_pushButtonPen_clicked();

    void on_pushButtonPenDuster_clicked();

    void on_pushButtonQuit_clicked();

    void on_pushButtonShape_clicked();

private:
    Ui::MainWindow *ui;
    DrawingWidget* widget;//Todo rename
    ShapeWidget* shapeWidget;

    bool isDragging = false;
    QPoint dragStart;
};
#endif // MAINWINDOW_H
