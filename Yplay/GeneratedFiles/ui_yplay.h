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
#include <QtWidgets/QLabel>
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
    QLabel *lable_ico;
    QPushButton *btn_open;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_min;
    QPushButton *btn_max;
    QPushButton *btn_exit;
    QOpenGLWidget *openGL_video;
    QSlider *bar_schedule;
    QHBoxLayout *control_layout;
    QPushButton *btn_backward;
    QPushButton *btn_play;
    QPushButton *btn_forward;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
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
        menu_layout->setContentsMargins(9, 5, 9, 5);
        lable_ico = new QLabel(centralWidget);
        lable_ico->setObjectName(QStringLiteral("lable_ico"));
        lable_ico->setMinimumSize(QSize(50, 50));
        lable_ico->setMaximumSize(QSize(50, 50));
        lable_ico->setStyleSheet(QStringLiteral("border-image: url(:/Resources/png/ico.png);"));

        menu_layout->addWidget(lable_ico);

        btn_open = new QPushButton(centralWidget);
        btn_open->setObjectName(QStringLiteral("btn_open"));
        btn_open->setMinimumSize(QSize(30, 30));
        btn_open->setMaximumSize(QSize(30, 30));
        btn_open->setStyleSheet(QLatin1String("QPushButton{\n"
"image:url(:/Resources/png/filord.png);\n"
"  color: white; \n"
"  border-radius: 10px; \n"
" border: 2px groove gray;\n"
"  border-style: outset;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color:white;\n"
" color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-style: inset;} \n"
""));

        menu_layout->addWidget(btn_open);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        menu_layout->addItem(horizontalSpacer);

        btn_min = new QPushButton(centralWidget);
        btn_min->setObjectName(QStringLiteral("btn_min"));
        btn_min->setMinimumSize(QSize(30, 30));
        btn_min->setMaximumSize(QSize(30, 30));
        btn_min->setStyleSheet(QLatin1String("QPushButton{\n"
"image:url(:/Resources/png/min.png);\n"
"  color: white; \n"
"  border-radius: 10px; \n"
" border: 2px groove gray;\n"
"  border-style: outset;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color:white;\n"
" color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-style: inset;} \n"
""));

        menu_layout->addWidget(btn_min);

        btn_max = new QPushButton(centralWidget);
        btn_max->setObjectName(QStringLiteral("btn_max"));
        btn_max->setMinimumSize(QSize(30, 30));
        btn_max->setStyleSheet(QLatin1String("QPushButton{\n"
"image:url(:/Resources/png/max.png);\n"
"  color: white; \n"
"  border-radius: 10px; \n"
" border: 2px groove gray;\n"
"  border-style: outset;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color:white;\n"
" color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-style: inset;} \n"
""));

        menu_layout->addWidget(btn_max);

        btn_exit = new QPushButton(centralWidget);
        btn_exit->setObjectName(QStringLiteral("btn_exit"));
        btn_exit->setMinimumSize(QSize(30, 30));
        btn_exit->setMaximumSize(QSize(30, 30));
        btn_exit->setStyleSheet(QLatin1String("QPushButton{\n"
"image:url(:/Resources/png/exit.png);\n"
"  color: white; \n"
"  border-radius: 10px; \n"
" border: 2px groove gray;\n"
"  border-style: outset;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color:white;\n"
" color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-style: inset;} \n"
""));

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
        control_layout->setSpacing(4);
        control_layout->setObjectName(QStringLiteral("control_layout"));
        control_layout->setContentsMargins(9, 5, 9, 5);
        btn_backward = new QPushButton(centralWidget);
        btn_backward->setObjectName(QStringLiteral("btn_backward"));
        btn_backward->setMinimumSize(QSize(30, 30));
        btn_backward->setMaximumSize(QSize(30, 30));
        btn_backward->setStyleSheet(QLatin1String("\n"
"QPushButton{\n"
"image:url(:/Resources/png/back.png);\n"
"  color: white; \n"
"  border-radius: 10px; \n"
" border: 2px groove gray;\n"
"  border-style: outset;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color:white;\n"
" color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-style: inset;} \n"
""));

        control_layout->addWidget(btn_backward);

        btn_play = new QPushButton(centralWidget);
        btn_play->setObjectName(QStringLiteral("btn_play"));
        btn_play->setMinimumSize(QSize(30, 30));
        btn_play->setMaximumSize(QSize(30, 30));
        btn_play->setStyleSheet(QStringLiteral("border-image: url(:/Resources/png/play_1.png);"));

        control_layout->addWidget(btn_play);

        btn_forward = new QPushButton(centralWidget);
        btn_forward->setObjectName(QStringLiteral("btn_forward"));
        btn_forward->setMinimumSize(QSize(30, 30));
        btn_forward->setMaximumSize(QSize(30, 30));
        btn_forward->setStyleSheet(QStringLiteral("border-image: url(:/Resources/png/forward.png);"));

        control_layout->addWidget(btn_forward);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        control_layout->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(30, 30));
        pushButton->setMaximumSize(QSize(30, 30));
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/Resources/png/set.png);"));

        control_layout->addWidget(pushButton);

        btn_volume = new QPushButton(centralWidget);
        btn_volume->setObjectName(QStringLiteral("btn_volume"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_volume->sizePolicy().hasHeightForWidth());
        btn_volume->setSizePolicy(sizePolicy);
        btn_volume->setMinimumSize(QSize(30, 30));
        btn_volume->setMaximumSize(QSize(30, 30));
        btn_volume->setStyleSheet(QLatin1String("border-image: url(:/Resources/png/volum_1.png);\n"
""));

        control_layout->addWidget(btn_volume);

        bar_volume = new QSlider(centralWidget);
        bar_volume->setObjectName(QStringLiteral("bar_volume"));
        bar_volume->setMaximumSize(QSize(150, 23));
        bar_volume->setStyleSheet(QStringLiteral(""));
        bar_volume->setOrientation(Qt::Horizontal);

        control_layout->addWidget(bar_volume);


        verticalLayout->addLayout(control_layout);

        YplayClass->setCentralWidget(centralWidget);

        retranslateUi(YplayClass);
        QObject::connect(btn_open, SIGNAL(clicked()), YplayClass, SLOT(btn_openFile_click()));

        QMetaObject::connectSlotsByName(YplayClass);
    } // setupUi

    void retranslateUi(QMainWindow *YplayClass)
    {
        YplayClass->setWindowTitle(QApplication::translate("YplayClass", "Yplay", 0));
        lable_ico->setText(QString());
        btn_open->setText(QString());
        btn_min->setText(QString());
        btn_max->setText(QString());
        btn_exit->setText(QString());
        btn_backward->setText(QString());
        btn_play->setText(QString());
        btn_forward->setText(QString());
        pushButton->setText(QString());
        btn_volume->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class YplayClass: public Ui_YplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YPLAY_H
