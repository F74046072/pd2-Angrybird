/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QLabel *shooter;
    QLabel *score;
    QLabel *nowscore;
    QLabel *restart;
    QLabel *exit;
    QLabel *win;
    QLabel *lose;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(960, 540));
        MainWindow->setMaximumSize(QSize(960, 540));
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 960, 640));
        shooter = new QLabel(centralWidget);
        shooter->setObjectName(QStringLiteral("shooter"));
        shooter->setGeometry(QRect(110, 150, 101, 181));
        shooter->setPixmap(QPixmap(QString::fromUtf8(":/shooter.png")));
        score = new QLabel(centralWidget);
        score->setObjectName(QStringLiteral("score"));
        score->setGeometry(QRect(50, 30, 101, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        score->setFont(font);
        nowscore = new QLabel(centralWidget);
        nowscore->setObjectName(QStringLiteral("nowscore"));
        nowscore->setGeometry(QRect(160, 50, 61, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        nowscore->setFont(font1);
        nowscore->setLayoutDirection(Qt::LeftToRight);
        nowscore->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        restart = new QLabel(centralWidget);
        restart->setObjectName(QStringLiteral("restart"));
        restart->setGeometry(QRect(420, 10, 111, 101));
        restart->setPixmap(QPixmap(QString::fromUtf8(":/restart.png")));
        exit = new QLabel(centralWidget);
        exit->setObjectName(QStringLiteral("exit"));
        exit->setGeometry(QRect(540, 20, 101, 91));
        exit->setPixmap(QPixmap(QString::fromUtf8(":/exit.png")));
        win = new QLabel(centralWidget);
        win->setObjectName(QStringLiteral("win"));
        win->setGeometry(QRect(270, 230, 131, 111));
        lose = new QLabel(centralWidget);
        lose->setObjectName(QStringLiteral("lose"));
        lose->setGeometry(QRect(490, 250, 111, 61));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        shooter->setText(QString());
        score->setText(QApplication::translate("MainWindow", "Score:", 0));
        nowscore->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        restart->setText(QString());
        exit->setText(QString());
        win->setText(QString());
        lose->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
