#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>
//#include <QMetaFile>
#include <QWheelEvent>


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
    //bool saveToEMF(const QString &filename);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;


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
    QPointF offset = QPointF(0, 0);
    qreal scale = 1.0;
    bool panActive = false;
    QPoint panStartPoint;
};

#endif // DRAWINGCANVAS_H
