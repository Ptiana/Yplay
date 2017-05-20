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
    QHBoxLayout *menu_layout;
    QPushButton *btn_open;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_min;
    QPushButton *btn_max;
    QPushButton *btn_exit;
    QOpenGLWidget *openGL_video;
    QSlider *bar_schedule;
    QHBoxLayout *control_layout;
    QPushButton *btn_play;
    QPushButton *btn_backward;
    QPushButton *btn_forward;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_volume;
    QSlider *bar_volume;

    void setupUi(QMainWindow *YplayClass)
    {
        if (YplayClass->objectName().isEmpty())
            YplayClass->setObjectName(QStringLiteral("YplayClass"));
        YplayClass->resize(600, 400);
        YplayClass->setMouseTracking(true);
        centralWidget = new QWidget(YplayClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(127, 119, 125);"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        menu_layout = new QHBoxLayout();
        menu_layout->setSpacing(6);
        menu_layout->setObjectName(QStringLiteral("menu_layout"));
        menu_layout->setContentsMargins(1, 1, -1, 2);
        btn_open = new QPushButton(centralWidget);
        btn_open->setObjectName(QStringLiteral("btn_open"));
        btn_open->setMaximumSize(QSize(33, 22));

        menu_layout->addWidget(btn_open);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        menu_layout->addItem(horizontalSpacer);

        btn_min = new QPushButton(centralWidget);
        btn_min->setObjectName(QStringLiteral("btn_min"));
        btn_min->setMaximumSize(QSize(33, 22));
        btn_min->setStyleSheet(QLatin1String("border-image: url(:/Resources/png/minimizeHovered.png);\n"
""));

        menu_layout->addWidget(btn_min);

        btn_max = new QPushButton(centralWidget);
        btn_max->setObjectName(QStringLiteral("btn_max"));
        btn_max->setMaximumSize(QSize(33, 22));
        btn_max->setStyleSheet(QLatin1String("border-image: url(:/Resources/png/maximizeHovered.png);\n"
""));

        menu_layout->addWidget(btn_max);

        btn_exit = new QPushButton(centralWidget);
        btn_exit->setObjectName(QStringLiteral("btn_exit"));
        btn_exit->setMaximumSize(QSize(33, 22));
        btn_exit->setStyleSheet(QStringLiteral("border-image: url(:/Resources/png/closeHovered.png);"));

        menu_layout->addWidget(btn_exit);


        verticalLayout->addLayout(menu_layout);

        openGL_video = new QOpenGLWidget(centralWidget);
        openGL_video->setObjectName(QStringLiteral("openGL_video"));
        openGL_video->setMouseTracking(true);

        verticalLayout->addWidget(openGL_video);

        bar_schedule = new QSlider(centralWidget);
        bar_schedule->setObjectName(QStringLiteral("bar_schedule"));
        bar_schedule->setStyleSheet(QLatin1String("QSlider{background-color:rgb(0,0,0)}\n"
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
        bar_schedule->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(bar_schedule);

        control_layout = new QHBoxLayout();
        control_layout->setSpacing(0);
        control_layout->setObjectName(QStringLiteral("control_layout"));
        control_layout->setContentsMargins(1, 1, 1, -1);
        btn_play = new QPushButton(centralWidget);
        btn_play->setObjectName(QStringLiteral("btn_play"));
        btn_play->setMaximumSize(QSize(30, 23));
        btn_play->setStyleSheet(QStringLiteral(""));

        control_layout->addWidget(btn_play);

        btn_backward = new QPushButton(centralWidget);
        btn_backward->setObjectName(QStringLiteral("btn_backward"));
        btn_backward->setMaximumSize(QSize(30, 23));
        btn_backward->setStyleSheet(QStringLiteral(""));

        control_layout->addWidget(btn_backward);

        btn_forward = new QPushButton(centralWidget);
        btn_forward->setObjectName(QStringLiteral("btn_forward"));
        btn_forward->setMaximumSize(QSize(30, 23));
        btn_forward->setStyleSheet(QStringLiteral(""));

        control_layout->addWidget(btn_forward);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        control_layout->addItem(horizontalSpacer_2);

        btn_volume = new QPushButton(centralWidget);
        btn_volume->setObjectName(QStringLiteral("btn_volume"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_volume->sizePolicy().hasHeightForWidth());
        btn_volume->setSizePolicy(sizePolicy);
        btn_volume->setMaximumSize(QSize(23, 23));
        btn_volume->setStyleSheet(QStringLiteral(""));

        control_layout->addWidget(btn_volume);

        bar_volume = new QSlider(centralWidget);
        bar_volume->setObjectName(QStringLiteral("bar_volume"));
        bar_volume->setMaximumSize(QSize(200, 23));
        bar_volume->setStyleSheet(QStringLiteral(""));
        bar_volume->setOrientation(Qt::Horizontal);

        control_layout->addWidget(bar_volume);


        verticalLayout->addLayout(control_layout);

        YplayClass->setCentralWidget(centralWidget);

        retranslateUi(YplayClass);

        QMetaObject::connectSlotsByName(YplayClass);
    } // setupUi

    void retranslateUi(QMainWindow *YplayClass)
    {
        YplayClass->setWindowTitle(QApplication::translate("YplayClass", "Yplay", 0));
        btn_open->setText(QApplication::translate("YplayClass", "\346\211\223\345\274\200", 0));
        btn_min->setText(QString());
        btn_max->setText(QString());
        btn_exit->setText(QString());
        btn_play->setText(QApplication::translate("YplayClass", "\346\222\255\346\224\276", 0));
        btn_backward->setText(QApplication::translate("YplayClass", "\345\233\236\351\200\200", 0));
        btn_forward->setText(QApplication::translate("YplayClass", "\345\277\253\350\277\233", 0));
        btn_volume->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class YplayClass: public Ui_YplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YPLAY_H
