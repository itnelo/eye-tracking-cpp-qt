/********************************************************************************
** Form generated from reading UI file 'capturedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTUREDIALOG_H
#define UI_CAPTUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CaptureDialog
{
public:
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *point1;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_6;
    QLabel *point2;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_8;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QLabel *point3;
    QSpacerItem *verticalSpacer_12;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *point4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *point5;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_9;
    QLabel *point6;
    QSpacerItem *verticalSpacer_10;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QLabel *point7;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_5;
    QLabel *point8;
    QSpacerItem *horizontalSpacer_14;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QLabel *point9;

    void setupUi(QDialog *CaptureDialog)
    {
        if (CaptureDialog->objectName().isEmpty())
            CaptureDialog->setObjectName(QStringLiteral("CaptureDialog"));
        CaptureDialog->setWindowModality(Qt::WindowModal);
        CaptureDialog->resize(1000, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CaptureDialog->sizePolicy().hasHeightForWidth());
        CaptureDialog->setSizePolicy(sizePolicy);
        CaptureDialog->setMinimumSize(QSize(1000, 1000));
        CaptureDialog->setAutoFillBackground(false);
        CaptureDialog->setModal(true);
        verticalLayout_11 = new QVBoxLayout(CaptureDialog);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(30, 30, 30, 30);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        point1 = new QLabel(CaptureDialog);
        point1->setObjectName(QStringLiteral("point1"));
        point1->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_6->addWidget(point1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        point2 = new QLabel(CaptureDialog);
        point2->setObjectName(QStringLiteral("point2"));
        point2->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_9->addWidget(point2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_12);


        verticalLayout_6->addLayout(horizontalLayout_9);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);


        gridLayout->addLayout(verticalLayout_6, 0, 1, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        point3 = new QLabel(CaptureDialog);
        point3->setObjectName(QStringLiteral("point3"));
        point3->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_4->addWidget(point3);


        verticalLayout_9->addLayout(horizontalLayout_4);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_12);


        gridLayout->addLayout(verticalLayout_9, 0, 2, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        point4 = new QLabel(CaptureDialog);
        point4->setObjectName(QStringLiteral("point4"));
        point4->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_7->addWidget(point4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        point5 = new QLabel(CaptureDialog);
        point5->setObjectName(QStringLiteral("point5"));
        point5->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_2->addWidget(point5);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_13);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);


        gridLayout->addLayout(verticalLayout_4, 1, 1, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_11);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        point6 = new QLabel(CaptureDialog);
        point6->setObjectName(QStringLiteral("point6"));
        point6->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_5->addWidget(point6);


        verticalLayout_8->addLayout(horizontalLayout_5);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_10);


        gridLayout->addLayout(verticalLayout_8, 1, 2, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        point7 = new QLabel(CaptureDialog);
        point7->setObjectName(QStringLiteral("point7"));
        point7->setEnabled(true);
        point7->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout->addWidget(point7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_3, 2, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        point8 = new QLabel(CaptureDialog);
        point8->setObjectName(QStringLiteral("point8"));
        point8->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_8->addWidget(point8);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);


        verticalLayout_5->addLayout(horizontalLayout_8);


        gridLayout->addLayout(verticalLayout_5, 2, 1, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_9);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        point9 = new QLabel(CaptureDialog);
        point9->setObjectName(QStringLiteral("point9"));
        point9->setPixmap(QPixmap(QString::fromUtf8(":/images/capture_point.png")));

        horizontalLayout_3->addWidget(point9);


        verticalLayout_7->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_7, 2, 2, 1, 1);


        verticalLayout_10->addLayout(gridLayout);

        verticalLayout_10->setStretch(0, 100);

        verticalLayout_11->addLayout(verticalLayout_10);


        retranslateUi(CaptureDialog);

        QMetaObject::connectSlotsByName(CaptureDialog);
    } // setupUi

    void retranslateUi(QDialog *CaptureDialog)
    {
        CaptureDialog->setWindowTitle(QApplication::translate("CaptureDialog", "Dialog", 0));
        point1->setText(QString());
        point2->setText(QString());
        point3->setText(QString());
        point4->setText(QString());
        point5->setText(QString());
        point6->setText(QString());
        point7->setText(QString());
        point8->setText(QString());
        point9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CaptureDialog: public Ui_CaptureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTUREDIALOG_H
