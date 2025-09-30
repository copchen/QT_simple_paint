#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    if (drawing) {
        painter.drawLine(startPoint, endPoint);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        startPoint = event->pos();
        endPoint = startPoint;
        update();
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawing) {
        endPoint = event->pos();
        update();
    }
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = false;
        update();
    }
}
