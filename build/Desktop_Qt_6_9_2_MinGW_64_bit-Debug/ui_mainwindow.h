/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "drawingcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFreehand;
    QAction *actionLine;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    DrawingCanvas *drawingCanvas;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(983, 660);
        actionFreehand = new QAction(MainWindow);
        actionFreehand->setObjectName("actionFreehand");
        actionFreehand->setMenuRole(QAction::MenuRole::NoRole);
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName("actionLine");
        actionLine->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(1, 0, 1, 1);
        drawingCanvas = new DrawingCanvas(centralwidget);
        drawingCanvas->setObjectName("drawingCanvas");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(drawingCanvas->sizePolicy().hasHeightForWidth());
        drawingCanvas->setSizePolicy(sizePolicy1);
        drawingCanvas->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        drawingCanvas->setAutoFillBackground(false);
        drawingCanvas->setStyleSheet(QString::fromUtf8("background-color: white; border: 1px solid gray;"));

        horizontalLayout->addWidget(drawingCanvas);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 983, 25));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addAction(actionLine);
        toolBar->addAction(actionFreehand);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionFreehand->setText(QCoreApplication::translate("MainWindow", "\320\232\320\270\321\201\321\202\321\214", nullptr));
        actionLine->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\320\260\321\217 \320\273\320\270\320\275\320\270\321\217", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
