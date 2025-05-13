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
    QPushButton *pvp;
    QPushButton *pve;
    QPushButton *esc;

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
        pvp = new QPushButton(widget);
        pvp->setObjectName("pvp");

        verticalLayout->addWidget(pvp);

        pve = new QPushButton(widget);
        pve->setObjectName("pve");

        verticalLayout->addWidget(pve);

        esc = new QPushButton(widget);
        esc->setObjectName("esc");

        verticalLayout->addWidget(esc);


        retranslateUi(chooseMenu);

        QMetaObject::connectSlotsByName(chooseMenu);
    } // setupUi

    void retranslateUi(QWidget *chooseMenu)
    {
        chooseMenu->setWindowTitle(QCoreApplication::translate("chooseMenu", "Form", nullptr));
        pvp->setText(QCoreApplication::translate("chooseMenu", "\345\217\214\344\272\272\345\257\271\346\210\230", nullptr));
        pve->setText(QCoreApplication::translate("chooseMenu", "AI\345\257\271\346\210\230", nullptr));
        esc->setText(QCoreApplication::translate("chooseMenu", "\350\277\224\345\233\236\344\270\212\344\270\200\347\272\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chooseMenu: public Ui_chooseMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEMENU_H
