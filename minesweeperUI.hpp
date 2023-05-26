/********************************************************************************
** Form generated from reading UI file 'minesweeperUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MINESWEEPERUI_H
#define MINESWEEPERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_game;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *button;
    QMenuBar *menubar;
    QMenu *menuNew_game;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(715, 473);
        actionNew_game = new QAction(MainWindow);
        actionNew_game->setObjectName(QString::fromUtf8("actionNew_game"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        button = new QPushButton(centralwidget);
        button->setObjectName(QString::fromUtf8("button"));

        verticalLayout->addWidget(button);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 715, 21));
        menuNew_game = new QMenu(menubar);
        menuNew_game->setObjectName(QString::fromUtf8("menuNew_game"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuNew_game->menuAction());
        menuNew_game->addAction(actionNew_game);
        toolBar->addAction(actionNew_game);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_game->setText(QCoreApplication::translate("MainWindow", "New game", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Hello, world!", nullptr));
        button->setText(QCoreApplication::translate("MainWindow", "Click", nullptr));
        menuNew_game->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MINESWEEPERUI_H
