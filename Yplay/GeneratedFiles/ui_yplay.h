/********************************************************************************
** Form generated from reading UI file 'yplay.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YPLAY_H
#define UI_YPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_YplayClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QOpenGLWidget *openGLWidget;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_5;
    QSlider *horizontalSlider_2;

    void setupUi(QMainWindow *YplayClass)
    {
        if (YplayClass->objectName().isEmpty())
            YplayClass->setObjectName(QStringLiteral("YplayClass"));
        YplayClass->resize(600, 400);
        YplayClass->setMouseTracking(true);
        centralWidget = new QWidget(YplayClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, -1, -1);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(33, 22));

        horizontalLayout->addWidget(pushButton_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(33, 22));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(33, 22));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(33, 22));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setMouseTracking(true);

        verticalLayout->addWidget(openGLWidget);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setStyleSheet(QLatin1String("QSlider{background-color:rgb(0,0,0)}\n"
"\n"
"QSlider::add-page:horizontal{background-color: rgb(87, 97, 106);  height:4px; }\n"
"QSlider::sub-page:horizontal {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));height:4px;}\n"
"\n"
"QSlider::add-page:hover:horizontal{   background-color: rgb(87, 97, 106);  height:6px; }\n"
"QSlider::sub-page:hover:horizontal {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));height:6px;}\n"
"\n"
"QSlider::handle:horizontal {margin-top:-2px; margin-bottom:-2px;border-radius:4px;  background: rgb(222,222,222); width:14px; height:18px;}\n"
"\n"
"QSlider::groove:horizontal {background:transparent;height:4px}QSlider::groove:hover:horizontal {background:transparent;height:6px}"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, -1, -1);
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setMaximumSize(QSize(30, 23));

        horizontalLayout_2->addWidget(pushButton_8);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setMaximumSize(QSize(30, 23));

        horizontalLayout_2->addWidget(pushButton_7);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMaximumSize(QSize(30, 23));

        horizontalLayout_2->addWidget(pushButton_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMaximumSize(QSize(23, 23));

        horizontalLayout_2->addWidget(pushButton_5);

        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setMaximumSize(QSize(200, 23));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);


        verticalLayout->addLayout(horizontalLayout_2);

        YplayClass->setCentralWidget(centralWidget);

        retranslateUi(YplayClass);

        QMetaObject::connectSlotsByName(YplayClass);
    } // setupUi

    void retranslateUi(QMainWindow *YplayClass)
    {
        YplayClass->setWindowTitle(QApplication::translate("YplayClass", "Yplay", 0));
        pushButton_4->setText(QApplication::translate("YplayClass", "\346\211\223\345\274\200", 0));
        pushButton_3->setText(QString());
        pushButton_2->setText(QString());
        pushButton->setText(QString());
        pushButton_8->setText(QApplication::translate("YplayClass", "\346\222\255\346\224\276", 0));
        pushButton_7->setText(QApplication::translate("YplayClass", "\345\233\236\351\200\200", 0));
        pushButton_6->setText(QApplication::translate("YplayClass", "\345\277\253\350\277\233", 0));
        pushButton_5->setText(QApplication::translate("YplayClass", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class YplayClass: public Ui_YplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YPLAY_H
