/********************************************************************************
** Form generated from reading UI file 'minesweeper_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MINESWEEPER_UI_H
#define MINESWEEPER_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_game;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdNumber_left;
    QSpacerItem *horizontalSpacer;
    QPushButton *mainbutton;
    QSpacerItem *horizontalSpacer_2;
    QLCDNumber *lcdNumber_right;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QMenu *menuNew_game;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(300, 300);
        actionNew_game = new QAction(MainWindow);
        actionNew_game->setObjectName(QString::fromUtf8("actionNew_game"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lcdNumber_left = new QLCDNumber(centralwidget);
        lcdNumber_left->setObjectName(QString::fromUtf8("lcdNumber_left"));
        lcdNumber_left->setMaximumSize(QSize(16777215, 75));

        horizontalLayout->addWidget(lcdNumber_left);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        mainbutton = new QPushButton(centralwidget);
        mainbutton->setObjectName(QString::fromUtf8("mainbutton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainbutton->sizePolicy().hasHeightForWidth());
        mainbutton->setSizePolicy(sizePolicy);
        mainbutton->setMinimumSize(QSize(75, 75));
        mainbutton->setMaximumSize(QSize(75, 75));
        mainbutton->setBaseSize(QSize(75, 75));

        horizontalLayout->addWidget(mainbutton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lcdNumber_right = new QLCDNumber(centralwidget);
        lcdNumber_right->setObjectName(QString::fromUtf8("lcdNumber_right"));
        lcdNumber_right->setMaximumSize(QSize(16777215, 75));

        horizontalLayout->addWidget(lcdNumber_right);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);

        horizontalLayout_3->addLayout(gridLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 300, 21));
        menuNew_game = new QMenu(menubar);
        menuNew_game->setObjectName(QString::fromUtf8("menuNew_game"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNew_game->menuAction());
        menuNew_game->addAction(actionNew_game);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Minesweeper", nullptr));
        actionNew_game->setText(QCoreApplication::translate("MainWindow", "New game", nullptr));
        mainbutton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        menuNew_game->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MINESWEEPER_UI_H
