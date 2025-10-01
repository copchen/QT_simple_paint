#include "drawingcanvas.h"
#include <QKeyEvent>
#include <QWheelEvent>

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
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(offset);
    painter.scale(scale, scale);
    painter.setPen(Qt::black);
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


    if (currentTool == Shape::Text && isTextInputActive && !currentText.isEmpty()) {
        painter.drawText(textStartPoint, currentText);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        panActive = true;
        panStartPoint = event->pos();
        setCursor(Qt::ClosedHandCursor);
        return;
    }

    if (event->button() == Qt::LeftButton) {
        QPointF transformedPoint = (event->pos() - offset) / scale;
        if (currentTool == Shape::Text) {
            if (!currentText.isEmpty()) {
                Shape shape;
                shape.type = Shape::Text;
                shape.start = textStartPoint;
                shape.text = currentText;
                shapes.append(shape);
                currentText.clear();
            }
            textStartPoint = transformedPoint.toPoint();
            currentText.clear();
            isTextInputActive = true;
            setFocus();
            update();
        } else {
            drawing = true;
            if (currentTool == Shape::Freehand) {
                currentPath.clear();
                currentPath.append(transformedPoint.toPoint());
            } else if (currentTool == Shape::Line || currentTool == Shape::Rectangle || currentTool == Shape::Ellipse) {
                startPoint = transformedPoint.toPoint();
                endPoint = startPoint;
            } else if (currentTool == Shape::Polyline || currentTool == Shape::Polygon) {
                if (currentPath.isEmpty()) {
                    currentPath.append(transformedPoint.toPoint());
                } else {
                    currentPath.append(transformedPoint.toPoint());
                }
            }
            update();
        }
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (panActive) {
        offset += event->pos() - panStartPoint;
        panStartPoint = event->pos();
        update();
        return;
    }

    if (drawing) {
        QPointF transformedPoint = (event->pos() - offset) / scale;
        if (currentTool == Shape::Freehand) {
            currentPath.append(transformedPoint.toPoint());
        } else if (currentTool == Shape::Line || currentTool == Shape::Rectangle || currentTool == Shape::Ellipse) {
            endPoint = transformedPoint.toPoint();
        }
        update();
    }
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        panActive = false;
        setCursor(Qt::ArrowCursor);
        return;
    }

    if (event->button() == Qt::LeftButton) {
        QPointF transformedPoint = (event->pos() - offset) / scale;
        if (currentTool == Shape::Line || currentTool == Shape::Rectangle || currentTool == Shape::Ellipse) {
            drawing = false;
            Shape shape;
            shape.type = currentTool;
            shape.start = startPoint;
            shape.end = transformedPoint.toPoint();
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

void DrawingCanvas::wheelEvent(QWheelEvent *event) {
    Qt::KeyboardModifiers modifiers = event->modifiers();
    qreal delta = event->angleDelta().y() / 120.0;

    if (modifiers.testFlag(Qt::ControlModifier)) {

        qreal scaleFactor = (delta > 0) ? 1.1 : 0.9;
        QPointF oldOffset = offset;
        qreal oldScale = scale;
        scale *= scaleFactor;
        scale = qMax(0.1, qMin(scale, 10.0));


        QPointF mousePos = event->position();
        offset = mousePos - (mousePos - oldOffset) * (scale / oldScale);
        update();
    }

    event->accept();
}
