/********************************************************************************
** Form generated from reading UI file 'choosemenu.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEMENU_H
#define UI_CHOOSEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chooseMenu
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *chooseMenu)
    {
        if (chooseMenu->objectName().isEmpty())
            chooseMenu->setObjectName("chooseMenu");
        chooseMenu->resize(400, 300);
        widget = new QWidget(chooseMenu);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(150, 130, 77, 86));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);


        retranslateUi(chooseMenu);

        QMetaObject::connectSlotsByName(chooseMenu);
    } // setupUi

    void retranslateUi(QWidget *chooseMenu)
    {
        chooseMenu->setWindowTitle(QCoreApplication::translate("chooseMenu", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("chooseMenu", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("chooseMenu", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("chooseMenu", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chooseMenu: public Ui_chooseMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEMENU_H
