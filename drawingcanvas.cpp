#include "drawingcanvas.h"
#include <QKeyEvent>

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void DrawingCanvas::setTool(Shape::Type tool) {
    currentTool = tool;
    if (currentTool != Shape::Text && !currentText.isEmpty()) {
        Shape shape;
        shape.type = Shape::Text;
        shape.start = textStartPoint;
        shape.text = currentText;
        shapes.append(shape);
        currentText.clear();
        isTextInputActive = false;
        update();
    }
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font("Arial", 12);
    painter.setFont(font);

    for (const Shape &shape : shapes) {
        if (shape.type == Shape::Line) {
            painter.drawLine(shape.start, shape.end);
        } else if (shape.type == Shape::Freehand) {
            for (int i = 1; i < shape.points.size(); ++i) {
                painter.drawLine(shape.points[i - 1], shape.points[i]);
            }
        } else if (shape.type == Shape::Rectangle) {
            painter.drawRect(QRect(shape.start, shape.end));
        } else if (shape.type == Shape::Polyline) {
            for (int i = 1; i < shape.points.size(); ++i) {
                painter.drawLine(shape.points[i - 1], shape.points[i]);
            }
        } else if (shape.type == Shape::Ellipse) {
            painter.drawEllipse(QRect(shape.start, shape.end));
        } else if (shape.type == Shape::Polygon) {
            painter.drawPolygon(shape.points.constData(), shape.points.size());
        } else if (shape.type == Shape::Text) {
            painter.drawText(shape.start, shape.text);
        }
    }

    if (drawing && currentTool == Shape::Freehand) {
        for (int i = 1; i < currentPath.size(); ++i) {
            painter.drawLine(currentPath[i - 1], currentPath[i]);
        }
    } else if (drawing && (currentTool == Shape::Line || currentTool == Shape::Rectangle || currentTool == Shape::Ellipse)) {
        if (currentTool == Shape::Line) {
            painter.drawLine(startPoint, endPoint);
        } else if (currentTool == Shape::Rectangle) {
            painter.drawRect(QRect(startPoint, endPoint));
        } else if (currentTool == Shape::Ellipse) {
            painter.drawEllipse(QRect(startPoint, endPoint));
        }
    } else if (drawing && (currentTool == Shape::Polyline || currentTool == Shape::Polygon)) {
        for (int i = 1; i < currentPath.size(); ++i) {
            painter.drawLine(currentPath[i - 1], currentPath[i]);
        }
    }

    // Отрисовка текущего текста
    if (currentTool == Shape::Text && isTextInputActive && !currentText.isEmpty()) {
        painter.drawText(textStartPoint, currentText);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (currentTool == Shape::Text) {
            if (!currentText.isEmpty()) {
                Shape shape;
                shape.type = Shape::Text;
                shape.start = textStartPoint;
                shape.text = currentText;
                shapes.append(shape);
                currentText.clear();
            }
            textStartPoint = event->pos();
            currentText.clear();
            isTextInputActive = true;
            setFocus();
            update();
        } else {
            drawing = true;
            if (currentTool == Shape::Freehand) {
                currentPath.clear();
                currentPath.append(event->pos());
            } else if (currentTool == Shape::Line || currentTool == Shape::Rectangle || currentTool == Shape::Ellipse) {
                startPoint = event->pos();
                endPoint = startPoint;
            } else if (currentTool == Shape::Polyline || currentTool == Shape::Polygon) {
                if (currentPath.isEmpty()) {
                    currentPath.append(event->pos());
                } else {
                    currentPath.append(event->pos());
                }
            }
            update();
        }
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawing) {
        if (currentTool == Shape::Freehand) {
            currentPath.append(event->pos());
        } else if (currentTool == Shape::Line || currentTool == Shape::Rectangle || currentTool == Shape::Ellipse) {
            endPoint = event->pos();
        }
        update();
    }
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (currentTool == Shape::Line || currentTool == Shape::Rectangle || currentTool == Shape::Ellipse) {
            drawing = false;
            Shape shape;
            shape.type = currentTool;
            shape.start = startPoint;
            shape.end = endPoint;
            shapes.append(shape);
            update();
        } else if (currentTool == Shape::Freehand) {
            drawing = false;
            Shape shape;
            shape.type = currentTool;
            shape.points = currentPath;
            shapes.append(shape);
            currentPath.clear();
            update();
        }
    }
}

void DrawingCanvas::mouseDoubleClickEvent(QMouseEvent *event) {
    if (drawing && (currentTool == Shape::Polyline || currentTool == Shape::Polygon)) {
        drawing = false;
        Shape shape;
        shape.type = currentTool;
        shape.points = currentPath;
        if (currentTool == Shape::Polygon && !currentPath.isEmpty()) {
            currentPath.append(currentPath.first());
            shape.points = currentPath;
        }
        shapes.append(shape);
        currentPath.clear();
        update();
    }
}

void DrawingCanvas::keyPressEvent(QKeyEvent *event) {
    if (currentTool == Shape::Text && isTextInputActive) {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            if (!currentText.isEmpty()) {
                Shape shape;
                shape.type = Shape::Text;
                shape.start = textStartPoint;
                shape.text = currentText;
                shapes.append(shape);
            }
            currentText.clear();
            isTextInputActive = false;
            update();
        } else if (event->key() == Qt::Key_Backspace) {
            if (!currentText.isEmpty()) {
                currentText.chop(1);
                update();
            }
        } else if (!event->text().isEmpty() && event->text()[0].isPrint()) {
            currentText += event->text();
            update();
        }
    } else {
        QWidget::keyPressEvent(event);
    }
}
