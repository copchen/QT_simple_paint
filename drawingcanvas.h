#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>

struct Shape {
    enum Type { Line, Freehand }; // Добавляем тип Freehand для кисти
    Type type;
    // Для прямой линии: начальная и конечная точки
    QPoint start;
    QPoint end;
    // Для свободного рисования: набор точек
    QVector<QPoint> points;
};

class DrawingCanvas : public QWidget {
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool drawing = false;
    Shape::Type currentTool = Shape::Freehand; // Текущий инструмент (по умолчанию кисть)
    QVector<QPoint> currentPath; // Текущий путь для свободного рисования
    QPoint startPoint; // Для прямой линии
    QPoint endPoint;   // Для прямой линии
    QVector<Shape> shapes; // Список сохранённых фигур
};

#endif // DRAWINGCANVAS_H
