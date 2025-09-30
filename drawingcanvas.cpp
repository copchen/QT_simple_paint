#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);

    // Рисуем все сохранённые фигуры
    for (const Shape &shape : shapes) {
        if (shape.type == Shape::Line) {
            painter.drawLine(shape.start, shape.end);
        } else if (shape.type == Shape::Freehand) {
            for (int i = 1; i < shape.points.size(); ++i) {
                painter.drawLine(shape.points[i - 1], shape.points[i]);
            }
        }
    }

    // Рисуем текущий путь (для свободного рисования)
    if (drawing && currentTool == Shape::Freehand) {
        for (int i = 1; i < currentPath.size(); ++i) {
            painter.drawLine(currentPath[i - 1], currentPath[i]);
        }
    }
    // Рисуем текущую прямую линию
    else if (drawing && currentTool == Shape::Line) {
        painter.drawLine(startPoint, endPoint);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        if (currentTool == Shape::Freehand) {
            currentPath.clear();
            currentPath.append(event->pos());
        } else if (currentTool == Shape::Line) {
            startPoint = event->pos();
            endPoint = startPoint;
        }
        update();
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawing) {
        if (currentTool == Shape::Freehand) {
            currentPath.append(event->pos());
        } else if (currentTool == Shape::Line) {
            endPoint = event->pos();
        }
        update();
    }
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = false;
        Shape shape;
        shape.type = currentTool;
        if (currentTool == Shape::Freehand) {
            shape.points = currentPath;
            currentPath.clear();
        } else if (currentTool == Shape::Line) {
            shape.start = startPoint;
            shape.end = endPoint;
        }
        shapes.append(shape);
        update();
    }
}
