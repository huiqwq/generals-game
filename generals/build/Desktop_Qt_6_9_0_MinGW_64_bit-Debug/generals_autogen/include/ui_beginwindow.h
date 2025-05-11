/********************************************************************************
** Form generated from reading UI file 'beginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEGINWINDOW_H
#define UI_BEGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BeginWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QTextEdit *nameText;
    QPushButton *pushButton;

    void setupUi(QWidget *BeginWindow)
    {
        if (BeginWindow->objectName().isEmpty())
            BeginWindow->setObjectName("BeginWindow");
        BeginWindow->resize(400, 300);
        horizontalLayoutWidget = new QWidget(BeginWindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(60, 80, 291, 73));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        nameLabel = new QLabel(horizontalLayoutWidget);
        nameLabel->setObjectName("nameLabel");

        horizontalLayout->addWidget(nameLabel);

        nameText = new QTextEdit(horizontalLayoutWidget);
        nameText->setObjectName("nameText");

        horizontalLayout->addWidget(nameText, 0, Qt::AlignmentFlag::AlignHCenter);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 6);
        pushButton = new QPushButton(BeginWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(130, 190, 121, 41));

        retranslateUi(BeginWindow);

        QMetaObject::connectSlotsByName(BeginWindow);
    } // setupUi

    void retranslateUi(QWidget *BeginWindow)
    {
        BeginWindow->setWindowTitle(QCoreApplication::translate("BeginWindow", "Form", nullptr));
        nameLabel->setText(QCoreApplication::translate("BeginWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">user_name:</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("BeginWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BeginWindow: public Ui_BeginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEGINWINDOW_H
