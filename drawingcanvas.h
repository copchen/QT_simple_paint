#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>


struct Shape {
   enum Type { Line, Freehand, Rectangle, Polyline, Ellipse, Polygon,Text };
    Type type;
    QPoint start;
    QPoint end;
    QVector<QPoint> points;
    QString text;
};


class DrawingCanvas : public QWidget {
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    void setTool(Shape::Type tool);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


private:
    bool drawing = false;
    Shape::Type currentTool = Shape::Freehand;
    QVector<QPoint> currentPath;
    QPoint startPoint;
    QPoint endPoint;
    QVector<Shape> shapes;
    QString currentText;
    QPoint textStartPoint;
    bool isTextInputActive = false;
};

#endif // DRAWINGCANVAS_H
