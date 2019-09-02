/********************************************************************************
** Form generated from reading UI file 'XVideoUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XVIDEOUI_H
#define UI_XVIDEOUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "xvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_XVideoUIClass
{
public:
    QPushButton *closeButton;
    QPushButton *minSizeButton;
    XVideoWidget *src1Video;
    QPushButton *openButton;
    QSlider *playSlider;
    XVideoWidget *desVideo;
    QLabel *contrastLabel;
    QSpinBox *brightSpinBox;
    QDoubleSpinBox *contrastSpinBox;
    QLabel *brightLabel;
    QPushButton *setButton;
    QPushButton *exportButton;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QLabel *pyDownLabel;
    QLabel *pyUpLabel;
    QSpinBox *pyDownSpinBox;
    QSpinBox *pyUpSpinBox;
    QLabel *label;
    QSpinBox *XClipSpin;
    QSpinBox *YClipSpin;
    QSpinBox *widthSpin;
    QSpinBox *heightSpin;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QComboBox *flipCombo;
    QLabel *flipLabel;
    QComboBox *rotateCombo;
    QLabel *rotateLabel;
    QLabel *label_2;
    QComboBox *grayComboBox;
    QSpinBox *markXspin;
    QSpinBox *markYspin;
    QDoubleSpinBox *markAspin;
    QPushButton *pushButton;
    XVideoWidget *src02Video;
    QPushButton *blendPushButton;
    QDoubleSpinBox *blendDoubleSpin;
    QPushButton *mergePushButton;
    QSlider *rightHorizontalSlider;
    QSlider *leftHorizontalSlider;
    QLabel *label_3;

    void setupUi(QWidget *XVideoUIClass)
    {
        if (XVideoUIClass->objectName().isEmpty())
            XVideoUIClass->setObjectName(QStringLiteral("XVideoUIClass"));
        XVideoUIClass->resize(992, 617);
        XVideoUIClass->setStyleSheet(QString::fromUtf8("QPushButton:hover\n"
" { \n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(120, 120, 120, 255), stop:0.495 rgba(39, 39, 39, 255), stop:0.505 rgba(39,39, 39, 255), stop:1 rgba(120, 120,120, 255));\n"
"border: none;\n"
"border-radius:5px;\n"
"color: rgb(255, 255, 255);\n"
"font: 75 12pt \"\351\273\221\344\275\223\";\n"
" }\n"
"QPushButton:!hover\n"
" { \n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(39, 39, 39, 255), stop:0.495 rgba(120, 120, 120, 255), stop:0.505 rgba(120,120, 120, 255), stop:1 rgba(39, 39,39, 255));\n"
"border: none;\n"
"border-radius:5px;\n"
"color: rgb(255, 255, 255);\n"
"font: 75 12pt \"\351\273\221\344\275\223\";\n"
" }\n"
"#XVideoUIClass\n"
"{\n"
"background-color: rgb(53, 53, 53);\n"
"}\n"
"#closeButton\n"
"{\n"
"font: 22pt \"\347\255\211\347\272\277\";\n"
"color: rgb(255, 255, 255);\n"
"}\n"
"#minSizeButton\n"
"{\n"
"font: 35pt \"\347\255\211\347\272\277\";\n"
"color: rgb(255, 255, 255);\n"
"}\n"
"QLabel\n"
"{\n"
""
                        "color: rgb(255, 255, 255);\n"
"}\n"
"#playButton\n"
"{\n"
"background-color: rgba(255, 255, 255, 0);\n"
"image: url(:/XVideoUI/Resources/PlayH.png);\n"
"}\n"
"#playButton:!hover\n"
"{\n"
"background-color:rgba(255, 255, 255, 0);\n"
"image: url(:/XVideoUI/Resources/PlayN.png);\n"
"}\n"
"\n"
"#playButton:pressed\n"
"{\n"
"background-color:rgba(255, 255, 255, 0);\n"
"image: url(:/XVideoUI/Resources/PlayP.png);\n"
"}\n"
"#pauseButton\n"
"{\n"
"background-color: rgba(255, 255, 255, 0);\n"
"image: url(:/XVideoUI/Resources/PauseH.png);\n"
"}\n"
"#pauseButton:!hover\n"
"{\n"
"background-color:rgba(255, 255, 255, 0);\n"
"image: url(:/XVideoUI/Resources/PauseN.png);\n"
"}\n"
"\n"
"#pauseButton:pressed\n"
"{\n"
"background-color:rgba(255, 255, 255, 0);\n"
"	image: url(:/XVideoUI/Resources/PauseP.png);\n"
"}\n"
""));
        closeButton = new QPushButton(XVideoUIClass);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(960, 0, 30, 30));
        closeButton->setStyleSheet(QStringLiteral(""));
        closeButton->setFlat(true);
        minSizeButton = new QPushButton(XVideoUIClass);
        minSizeButton->setObjectName(QStringLiteral("minSizeButton"));
        minSizeButton->setGeometry(QRect(930, 0, 30, 30));
        minSizeButton->setFlat(true);
        src1Video = new XVideoWidget(XVideoUIClass);
        src1Video->setObjectName(QStringLiteral("src1Video"));
        src1Video->setGeometry(QRect(10, 30, 480, 280));
        openButton = new QPushButton(XVideoUIClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(700, 330, 71, 23));
        playSlider = new QSlider(XVideoUIClass);
        playSlider->setObjectName(QStringLiteral("playSlider"));
        playSlider->setGeometry(QRect(10, 330, 481, 31));
        playSlider->setStyleSheet(QLatin1String("\n"
"QSlider::groove:horizontal {\n"
"border: 1px solid #4A708B;\n"
"background: #C0C0C0;\n"
"height: 5px;\n"
"border-radius: 1px;\n"
"padding-left:-1px;\n"
"padding-right:-1px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \n"
"    stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\n"
"    stop: 0 #5DCCFF, stop: 1 #1874CD);\n"
"border: 1px solid #4A708B;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal {\n"
"background: #575757;\n"
"border: 0px solid #777;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal \n"
"{\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, \n"
"    stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:hover {\n"
"    bac"
                        "kground: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA, \n"
"    stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #00009C;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
""));
        playSlider->setMaximum(999);
        playSlider->setOrientation(Qt::Horizontal);
        desVideo = new XVideoWidget(XVideoUIClass);
        desVideo->setObjectName(QStringLiteral("desVideo"));
        desVideo->setGeometry(QRect(500, 30, 480, 280));
        contrastLabel = new QLabel(XVideoUIClass);
        contrastLabel->setObjectName(QStringLiteral("contrastLabel"));
        contrastLabel->setGeometry(QRect(550, 490, 41, 20));
        brightSpinBox = new QSpinBox(XVideoUIClass);
        brightSpinBox->setObjectName(QStringLiteral("brightSpinBox"));
        brightSpinBox->setGeometry(QRect(610, 450, 71, 20));
        brightSpinBox->setMinimum(1);
        brightSpinBox->setMaximum(100);
        contrastSpinBox = new QDoubleSpinBox(XVideoUIClass);
        contrastSpinBox->setObjectName(QStringLiteral("contrastSpinBox"));
        contrastSpinBox->setGeometry(QRect(610, 490, 71, 18));
        contrastSpinBox->setMaximum(3);
        brightLabel = new QLabel(XVideoUIClass);
        brightLabel->setObjectName(QStringLiteral("brightLabel"));
        brightLabel->setGeometry(QRect(560, 447, 31, 21));
        setButton = new QPushButton(XVideoUIClass);
        setButton->setObjectName(QStringLiteral("setButton"));
        setButton->setGeometry(QRect(930, 490, 51, 51));
        exportButton = new QPushButton(XVideoUIClass);
        exportButton->setObjectName(QStringLiteral("exportButton"));
        exportButton->setGeometry(QRect(790, 330, 75, 23));
        playButton = new QPushButton(XVideoUIClass);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(540, 320, 41, 41));
        pauseButton = new QPushButton(XVideoUIClass);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setGeometry(QRect(620, 320, 41, 41));
        pyDownLabel = new QLabel(XVideoUIClass);
        pyDownLabel->setObjectName(QStringLiteral("pyDownLabel"));
        pyDownLabel->setGeometry(QRect(720, 450, 90, 20));
        pyUpLabel = new QLabel(XVideoUIClass);
        pyUpLabel->setObjectName(QStringLiteral("pyUpLabel"));
        pyUpLabel->setGeometry(QRect(710, 480, 90, 20));
        pyDownSpinBox = new QSpinBox(XVideoUIClass);
        pyDownSpinBox->setObjectName(QStringLiteral("pyDownSpinBox"));
        pyDownSpinBox->setGeometry(QRect(810, 450, 98, 22));
        pyUpSpinBox = new QSpinBox(XVideoUIClass);
        pyUpSpinBox->setObjectName(QStringLiteral("pyUpSpinBox"));
        pyUpSpinBox->setGeometry(QRect(810, 480, 98, 22));
        label = new QLabel(XVideoUIClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(501, 410, 151, 16));
        XClipSpin = new QSpinBox(XVideoUIClass);
        XClipSpin->setObjectName(QStringLiteral("XClipSpin"));
        XClipSpin->setGeometry(QRect(730, 410, 57, 18));
        XClipSpin->setMaximum(9999);
        YClipSpin = new QSpinBox(XVideoUIClass);
        YClipSpin->setObjectName(QStringLiteral("YClipSpin"));
        YClipSpin->setGeometry(QRect(660, 410, 57, 18));
        YClipSpin->setMaximum(9999);
        widthSpin = new QSpinBox(XVideoUIClass);
        widthSpin->setObjectName(QStringLiteral("widthSpin"));
        widthSpin->setGeometry(QRect(800, 410, 57, 18));
        widthSpin->setMaximum(9999);
        widthSpin->setSingleStep(100);
        heightSpin = new QSpinBox(XVideoUIClass);
        heightSpin->setObjectName(QStringLiteral("heightSpin"));
        heightSpin->setGeometry(QRect(860, 410, 57, 18));
        heightSpin->setMaximum(9999);
        heightSpin->setSingleStep(100);
        widthLabel = new QLabel(XVideoUIClass);
        widthLabel->setObjectName(QStringLiteral("widthLabel"));
        widthLabel->setGeometry(QRect(520, 530, 71, 20));
        heightLabel = new QLabel(XVideoUIClass);
        heightLabel->setObjectName(QStringLiteral("heightLabel"));
        heightLabel->setGeometry(QRect(520, 570, 81, 20));
        widthSpinBox = new QSpinBox(XVideoUIClass);
        widthSpinBox->setObjectName(QStringLiteral("widthSpinBox"));
        widthSpinBox->setGeometry(QRect(610, 530, 71, 18));
        widthSpinBox->setMaximum(99999);
        heightSpinBox = new QSpinBox(XVideoUIClass);
        heightSpinBox->setObjectName(QStringLiteral("heightSpinBox"));
        heightSpinBox->setGeometry(QRect(610, 570, 71, 18));
        heightSpinBox->setMaximum(99999);
        flipCombo = new QComboBox(XVideoUIClass);
        flipCombo->setObjectName(QStringLiteral("flipCombo"));
        flipCombo->setGeometry(QRect(810, 540, 98, 20));
        flipLabel = new QLabel(XVideoUIClass);
        flipLabel->setObjectName(QStringLiteral("flipLabel"));
        flipLabel->setGeometry(QRect(737, 540, 61, 20));
        rotateCombo = new QComboBox(XVideoUIClass);
        rotateCombo->setObjectName(QStringLiteral("rotateCombo"));
        rotateCombo->setGeometry(QRect(810, 510, 98, 20));
        rotateLabel = new QLabel(XVideoUIClass);
        rotateLabel->setObjectName(QStringLiteral("rotateLabel"));
        rotateLabel->setGeometry(QRect(740, 510, 90, 20));
        label_2 = new QLabel(XVideoUIClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(730, 570, 71, 20));
        grayComboBox = new QComboBox(XVideoUIClass);
        grayComboBox->setObjectName(QStringLiteral("grayComboBox"));
        grayComboBox->setGeometry(QRect(810, 570, 98, 22));
        markXspin = new QSpinBox(XVideoUIClass);
        markXspin->setObjectName(QStringLiteral("markXspin"));
        markXspin->setGeometry(QRect(660, 381, 57, 18));
        markXspin->setMaximum(99999);
        markYspin = new QSpinBox(XVideoUIClass);
        markYspin->setObjectName(QStringLiteral("markYspin"));
        markYspin->setGeometry(QRect(730, 381, 57, 18));
        markYspin->setMaximum(99999);
        markAspin = new QDoubleSpinBox(XVideoUIClass);
        markAspin->setObjectName(QStringLiteral("markAspin"));
        markAspin->setGeometry(QRect(800, 381, 117, 18));
        markAspin->setMinimum(0.4);
        markAspin->setMaximum(1);
        markAspin->setSingleStep(0.1);
        pushButton = new QPushButton(XVideoUIClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(502, 382, 152, 16));
        src02Video = new XVideoWidget(XVideoUIClass);
        src02Video->setObjectName(QStringLiteral("src02Video"));
        src02Video->setGeometry(QRect(10, 390, 352, 200));
        blendPushButton = new QPushButton(XVideoUIClass);
        blendPushButton->setObjectName(QStringLiteral("blendPushButton"));
        blendPushButton->setGeometry(QRect(380, 480, 121, 23));
        blendDoubleSpin = new QDoubleSpinBox(XVideoUIClass);
        blendDoubleSpin->setObjectName(QStringLiteral("blendDoubleSpin"));
        blendDoubleSpin->setGeometry(QRect(450, 520, 51, 22));
        blendDoubleSpin->setMinimum(0.1);
        blendDoubleSpin->setMaximum(1);
        blendDoubleSpin->setSingleStep(0.1);
        mergePushButton = new QPushButton(XVideoUIClass);
        mergePushButton->setObjectName(QStringLiteral("mergePushButton"));
        mergePushButton->setGeometry(QRect(380, 440, 121, 23));
        rightHorizontalSlider = new QSlider(XVideoUIClass);
        rightHorizontalSlider->setObjectName(QStringLiteral("rightHorizontalSlider"));
        rightHorizontalSlider->setGeometry(QRect(10, 360, 481, 22));
        rightHorizontalSlider->setStyleSheet(QLatin1String("QScrollBar:horizontal{\n"
"    height:12px;\n"
"    border:1px solid rgba(0,0,0,50);\n"
"    margin:0px,0px,0px,0px;\n"
"    padding-left:15px;\n"
"    padding-right:15px;\n"
"}\n"
"QScrollBar::handle:horizontal{\n"
"    height:16px;\n"
"    background:rgba(0,0,0,25%);\n"
"    min-width:20;\n"
"}\n"
"QScrollBar::handle:horizontal:hover{\n"
"    background:rgba(0,0,0,50%);\n"
"    border:0px rgba(0,0,0,25%);\n"
"}\n"
"QScrollBar::sub-line:horizontal{\n"
"    width:15px;\n"
"    border-image:url(:/Res/scroll_left.png);\n"
"    subcontrol-position:left;\n"
"}\n"
"QScrollBar::sub-line:horizontal:hover{\n"
"    width:15px;\n"
"    background:rgba(0,0,0,25%);\n"
"    subcontrol-position:left;\n"
"}\n"
"QScrollBar::add-line:horizontal{\n"
"    width:15px;\n"
"    border-image:url(:/Res/scroll_right.png);\n"
"    subcontrol-position:right;\n"
"}\n"
"QScrollBar::add-line:horizontal:hover{\n"
"    width:15px;\n"
"    background:rgba(0,0,0,25%);\n"
"    subcontrol-position:right;\n"
"}\n"
"QScrollBar::add-page:horizontal"
                        "{\n"
"    background:rgb(255,255,255);\n"
"}\n"
"QScrollBar::sub-page:horizontal{\n"
"    background:rgb(255,255,255);\n"
"}\n"
""));
        rightHorizontalSlider->setMaximum(999);
        rightHorizontalSlider->setOrientation(Qt::Horizontal);
        leftHorizontalSlider = new QSlider(XVideoUIClass);
        leftHorizontalSlider->setObjectName(QStringLiteral("leftHorizontalSlider"));
        leftHorizontalSlider->setGeometry(QRect(10, 310, 481, 22));
        leftHorizontalSlider->setStyleSheet(QLatin1String("QScrollBar:horizontal{\n"
"    height:12px;\n"
"    border:1px solid rgba(0,0,0,50);\n"
"    margin:0px,0px,0px,0px;\n"
"    padding-left:15px;\n"
"    padding-right:15px;\n"
"}\n"
"QScrollBar::handle:horizontal{\n"
"    height:16px;\n"
"    background:rgba(0,0,0,25%);\n"
"    min-width:20;\n"
"}\n"
"QScrollBar::handle:horizontal:hover{\n"
"    background:rgba(0,0,0,50%);\n"
"    border:0px rgba(0,0,0,25%);\n"
"}\n"
"QScrollBar::sub-line:horizontal{\n"
"    width:15px;\n"
"    border-image:url(:/Res/scroll_left.png);\n"
"    subcontrol-position:left;\n"
"}\n"
"QScrollBar::sub-line:horizontal:hover{\n"
"    width:15px;\n"
"    background:rgba(0,0,0,25%);\n"
"    subcontrol-position:left;\n"
"}\n"
"QScrollBar::add-line:horizontal{\n"
"    width:15px;\n"
"    border-image:url(:/Res/scroll_right.png);\n"
"    subcontrol-position:right;\n"
"}\n"
"QScrollBar::add-line:horizontal:hover{\n"
"    width:15px;\n"
"    background:rgba(0,0,0,25%);\n"
"    subcontrol-position:right;\n"
"}\n"
"QScrollBar::add-page:horizontal"
                        "{\n"
"    background:rgb(255,255,255);\n"
"}\n"
"QScrollBar::sub-page:horizontal{\n"
"    background:rgb(255,255,255);\n"
"}\n"
"\n"
""));
        leftHorizontalSlider->setMaximum(999);
        leftHorizontalSlider->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(XVideoUIClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(380, 520, 61, 20));

        retranslateUi(XVideoUIClass);
        QObject::connect(closeButton, SIGNAL(clicked()), XVideoUIClass, SLOT(close()));
        QObject::connect(minSizeButton, SIGNAL(clicked()), XVideoUIClass, SLOT(showMinimized()));
        QObject::connect(openButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Open()));
        QObject::connect(playSlider, SIGNAL(sliderMoved(int)), XVideoUIClass, SLOT(setPos(int)));
        QObject::connect(playSlider, SIGNAL(sliderPressed()), XVideoUIClass, SLOT(sliderPress()));
        QObject::connect(playSlider, SIGNAL(sliderReleased()), XVideoUIClass, SLOT(sliderRelease()));
        QObject::connect(setButton, SIGNAL(clicked()), XVideoUIClass, SLOT(set()));
        QObject::connect(exportButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Export()));
        QObject::connect(playButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Play()));
        QObject::connect(pauseButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Pause()));
        QObject::connect(pushButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Mark()));
        QObject::connect(blendPushButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Blend()));
        QObject::connect(mergePushButton, SIGNAL(clicked()), XVideoUIClass, SLOT(Merge()));
        QObject::connect(leftHorizontalSlider, SIGNAL(sliderMoved(int)), XVideoUIClass, SLOT(Left(int)));
        QObject::connect(rightHorizontalSlider, SIGNAL(sliderMoved(int)), XVideoUIClass, SLOT(Right(int)));

        QMetaObject::connectSlotsByName(XVideoUIClass);
    } // setupUi

    void retranslateUi(QWidget *XVideoUIClass)
    {
        XVideoUIClass->setWindowTitle(QApplication::translate("XVideoUIClass", "XVideoUI", 0));
        closeButton->setText(QApplication::translate("XVideoUIClass", "X", 0));
        minSizeButton->setText(QApplication::translate("XVideoUIClass", "-", 0));
        openButton->setText(QApplication::translate("XVideoUIClass", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        contrastLabel->setText(QApplication::translate("XVideoUIClass", "\345\257\271\346\257\224\345\272\246", 0));
        brightLabel->setText(QApplication::translate("XVideoUIClass", "\344\272\256\345\272\246", 0));
        setButton->setText(QApplication::translate("XVideoUIClass", "\350\256\276\347\275\256", 0));
        exportButton->setText(QApplication::translate("XVideoUIClass", "\345\257\274\345\207\272\350\247\206\351\242\221", 0));
        playButton->setText(QString());
        pauseButton->setText(QString());
        pyDownLabel->setText(QApplication::translate("XVideoUIClass", "  \351\253\230\346\226\257\351\207\221\345\255\227\345\241\224", 0));
        pyUpLabel->setText(QApplication::translate("XVideoUIClass", "\346\213\211\346\231\256\346\213\211\346\226\257\351\207\221\345\255\227\345\241\224", 0));
        label->setText(QApplication::translate("XVideoUIClass", "\350\247\206\351\242\221\350\243\201\345\211\252 x,y,width,height", 0));
        widthLabel->setText(QApplication::translate("XVideoUIClass", "\350\276\223\345\207\272\350\247\206\351\242\221\345\256\275\345\272\246", 0));
        heightLabel->setText(QApplication::translate("XVideoUIClass", "\350\276\223\345\207\272\350\247\206\351\242\221\351\253\230\345\272\246", 0));
        flipCombo->clear();
        flipCombo->insertItems(0, QStringList()
         << QApplication::translate("XVideoUIClass", "\344\270\215\345\201\232\351\225\234\345\203\217", 0)
         << QApplication::translate("XVideoUIClass", "\344\270\212\344\270\213\351\225\234\345\203\217", 0)
         << QApplication::translate("XVideoUIClass", "\345\267\246\345\217\263\351\225\234\345\203\217", 0)
         << QApplication::translate("XVideoUIClass", "\344\270\212\344\270\213\345\267\246\345\217\263\351\225\234\345\203\217", 0)
        );
        flipLabel->setText(QApplication::translate("XVideoUIClass", " \345\233\276\345\203\217\351\225\234\345\203\217", 0));
        rotateCombo->clear();
        rotateCombo->insertItems(0, QStringList()
         << QApplication::translate("XVideoUIClass", "0", 0)
         << QApplication::translate("XVideoUIClass", "90", 0)
         << QApplication::translate("XVideoUIClass", "180", 0)
         << QApplication::translate("XVideoUIClass", "270", 0)
        );
        rotateLabel->setText(QApplication::translate("XVideoUIClass", " \345\233\276\345\203\217\346\227\213\350\275\254", 0));
        label_2->setText(QApplication::translate("XVideoUIClass", "  \345\233\276\345\203\217\351\242\234\350\211\262", 0));
        grayComboBox->clear();
        grayComboBox->insertItems(0, QStringList()
         << QApplication::translate("XVideoUIClass", "\346\231\256\351\200\232RGB\345\233\276\345\203\217", 0)
         << QApplication::translate("XVideoUIClass", "\347\201\260\345\272\246\345\233\276", 0)
        );
        pushButton->setText(QApplication::translate("XVideoUIClass", "\346\267\273\345\212\240\346\260\264\345\215\260 X,Y,\351\200\217\346\230\216\345\272\246", 0));
        blendPushButton->setText(QApplication::translate("XVideoUIClass", "\350\247\206\351\242\221\350\236\215\345\220\210", 0));
        mergePushButton->setText(QApplication::translate("XVideoUIClass", "\350\247\206\351\242\221\345\220\210\345\271\266", 0));
        label_3->setText(QApplication::translate("XVideoUIClass", "\350\236\215\345\220\210\351\200\217\346\230\216\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class XVideoUIClass: public Ui_XVideoUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XVIDEOUI_H
