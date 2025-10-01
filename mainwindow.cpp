#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas = findChild<DrawingCanvas*>("drawingCanvas");

    connect(ui->actionFreehand, &QAction::triggered, this, [this]() {
        if (canvas) canvas->setTool(Shape::Freehand);
    });
    connect(ui->actionLine, &QAction::triggered, this, [this]() {
        if (canvas) canvas->setTool(Shape::Line);
    });
    connect(ui->actionRectangle, &QAction::triggered, this, [this]() {
        if (canvas) canvas->setTool(Shape::Rectangle);
    });
    connect(ui->actionPolyline, &QAction::triggered, this, [this]() {
        if (canvas) canvas->setTool(Shape::Polyline);
    });
    connect(ui->actionEllipse, &QAction::triggered, this, [this]() {
        if (canvas) canvas->setTool(Shape::Ellipse);
    });
    connect(ui->actionPolygon, &QAction::triggered, this, [this]() {
        if (canvas) canvas->setTool(Shape::Polygon);
    });
    connect(ui->actionText, &QAction::triggered, this, [this]() {
        if (canvas) canvas->setTool(Shape::Text);
    });

    setMinimumSize(800, 600);
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
