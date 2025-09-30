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

    setMinimumSize(800, 600);
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
