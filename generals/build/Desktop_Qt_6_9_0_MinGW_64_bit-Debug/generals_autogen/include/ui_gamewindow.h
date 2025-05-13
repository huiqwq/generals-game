/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewindow
{
public:
    QWidget *mapWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gamewindow)
    {
        if (gamewindow->objectName().isEmpty())
            gamewindow->setObjectName("gamewindow");
        gamewindow->resize(488, 406);
        mapWidget = new QWidget(gamewindow);
        mapWidget->setObjectName("mapWidget");
        gamewindow->setCentralWidget(mapWidget);
        menubar = new QMenuBar(gamewindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 488, 22));
        gamewindow->setMenuBar(menubar);
        statusbar = new QStatusBar(gamewindow);
        statusbar->setObjectName("statusbar");
        gamewindow->setStatusBar(statusbar);

        retranslateUi(gamewindow);

        QMetaObject::connectSlotsByName(gamewindow);
    } // setupUi

    void retranslateUi(QMainWindow *gamewindow)
    {
        gamewindow->setWindowTitle(QCoreApplication::translate("gamewindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewindow: public Ui_gamewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
