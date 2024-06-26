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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdNumber_left;
    QSpacerItem *horizontalSpacer;
    QPushButton *flagButton;
    QPushButton *mainbutton;
    QPushButton *uncoverButton;
    QSpacerItem *horizontalSpacer_2;
    QLCDNumber *lcdNumber_right;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *buttonLayout;
    QPushButton *statisticsButton;
    QPushButton *beginnerButton;
    QPushButton *intermediateButton;
    QPushButton *expertButton;
    QPushButton *customButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(650, 780);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/logo")));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lcdNumber_left = new QLCDNumber(centralwidget);
        lcdNumber_left->setObjectName(QString::fromUtf8("lcdNumber_left"));
        lcdNumber_left->setMinimumSize(QSize(80, 0));
        lcdNumber_left->setMaximumSize(QSize(16777215, 75));
        lcdNumber_left->setDigitCount(4);
        lcdNumber_left->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(lcdNumber_left);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        flagButton = new QPushButton(centralwidget);
        flagButton->setObjectName(QString::fromUtf8("flagButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(flagButton->sizePolicy().hasHeightForWidth());
        flagButton->setSizePolicy(sizePolicy);
        flagButton->setMinimumSize(QSize(75, 75));
        flagButton->setMaximumSize(QSize(75, 75));
        flagButton->setBaseSize(QSize(75, 75));
        QFont font;
        font.setPointSize(25);
        flagButton->setFont(font);
        flagButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        horizontalLayout->addWidget(flagButton);

        mainbutton = new QPushButton(centralwidget);
        mainbutton->setObjectName(QString::fromUtf8("mainbutton"));
        sizePolicy.setHeightForWidth(mainbutton->sizePolicy().hasHeightForWidth());
        mainbutton->setSizePolicy(sizePolicy);
        mainbutton->setMinimumSize(QSize(75, 75));
        mainbutton->setMaximumSize(QSize(75, 75));
        mainbutton->setBaseSize(QSize(75, 75));
        mainbutton->setFont(font);
        mainbutton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        horizontalLayout->addWidget(mainbutton);

        uncoverButton = new QPushButton(centralwidget);
        uncoverButton->setObjectName(QString::fromUtf8("uncoverButton"));
        sizePolicy.setHeightForWidth(uncoverButton->sizePolicy().hasHeightForWidth());
        uncoverButton->setSizePolicy(sizePolicy);
        uncoverButton->setMinimumSize(QSize(75, 75));
        uncoverButton->setMaximumSize(QSize(75, 75));
        uncoverButton->setBaseSize(QSize(75, 75));
        uncoverButton->setFont(font);
        uncoverButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        horizontalLayout->addWidget(uncoverButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lcdNumber_right = new QLCDNumber(centralwidget);
        lcdNumber_right->setObjectName(QString::fromUtf8("lcdNumber_right"));
        lcdNumber_right->setMinimumSize(QSize(80, 0));
        lcdNumber_right->setMaximumSize(QSize(16777215, 75));
        lcdNumber_right->setDigitCount(4);
        lcdNumber_right->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(lcdNumber_right);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);

        horizontalLayout_3->addLayout(gridLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        statisticsButton = new QPushButton(centralwidget);
        statisticsButton->setObjectName(QString::fromUtf8("statisticsButton"));
        statisticsButton->setMinimumSize(QSize(50, 50));
        statisticsButton->setMaximumSize(QSize(50, 50));
        QFont font1;
        font1.setPointSize(22);
        statisticsButton->setFont(font1);
        statisticsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        buttonLayout->addWidget(statisticsButton);

        beginnerButton = new QPushButton(centralwidget);
        beginnerButton->setObjectName(QString::fromUtf8("beginnerButton"));
        sizePolicy.setHeightForWidth(beginnerButton->sizePolicy().hasHeightForWidth());
        beginnerButton->setSizePolicy(sizePolicy);
        beginnerButton->setMinimumSize(QSize(135, 32));
        beginnerButton->setMaximumSize(QSize(135, 32));
        beginnerButton->setBaseSize(QSize(150, 30));
        QFont font2;
        font2.setPointSize(12);
        beginnerButton->setFont(font2);
        beginnerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        buttonLayout->addWidget(beginnerButton);

        intermediateButton = new QPushButton(centralwidget);
        intermediateButton->setObjectName(QString::fromUtf8("intermediateButton"));
        sizePolicy.setHeightForWidth(intermediateButton->sizePolicy().hasHeightForWidth());
        intermediateButton->setSizePolicy(sizePolicy);
        intermediateButton->setMinimumSize(QSize(135, 32));
        intermediateButton->setMaximumSize(QSize(135, 32));
        intermediateButton->setBaseSize(QSize(100, 30));
        intermediateButton->setFont(font2);
        intermediateButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        buttonLayout->addWidget(intermediateButton);

        expertButton = new QPushButton(centralwidget);
        expertButton->setObjectName(QString::fromUtf8("expertButton"));
        sizePolicy.setHeightForWidth(expertButton->sizePolicy().hasHeightForWidth());
        expertButton->setSizePolicy(sizePolicy);
        expertButton->setMinimumSize(QSize(135, 32));
        expertButton->setMaximumSize(QSize(135, 32));
        expertButton->setBaseSize(QSize(150, 30));
        expertButton->setFont(font2);
        expertButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        buttonLayout->addWidget(expertButton);

        customButton = new QPushButton(centralwidget);
        customButton->setObjectName(QString::fromUtf8("customButton"));
        sizePolicy.setHeightForWidth(customButton->sizePolicy().hasHeightForWidth());
        customButton->setSizePolicy(sizePolicy);
        customButton->setMinimumSize(QSize(135, 32));
        customButton->setMaximumSize(QSize(135, 32));
        customButton->setBaseSize(QSize(100, 30));
        customButton->setFont(font2);
        customButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #ddd;\n"
"}\n"
""));

        buttonLayout->addWidget(customButton);


        verticalLayout_2->addLayout(buttonLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Minesweeper", nullptr));
        centralwidget->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"     QWidget#centralwidget {\n"
"         background-image: url(:/background);\n"
"         background-repeat: no-repeat;\n"
"         background-position: center;\n"
"     }\n"
"    ", nullptr));
        lcdNumber_left->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"                QLCDNumber {\n"
"                    background-color: white;\n"
"                    border-radius: 10px;\n"
"                }\n"
"            ", nullptr));
        flagButton->setText(QCoreApplication::translate("MainWindow", "\360\237\232\251", nullptr));
        mainbutton->setText(QCoreApplication::translate("MainWindow", "\360\237\231\202", nullptr));
        uncoverButton->setText(QCoreApplication::translate("MainWindow", "\342\233\217\357\270\217", nullptr));
        lcdNumber_right->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"                QLCDNumber {\n"
"                    background-color: white;\n"
"                    border-radius: 10px;\n"
"                }\n"
"            ", nullptr));
        statisticsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212", nullptr));
        beginnerButton->setText(QCoreApplication::translate("MainWindow", "BEGINNER", nullptr));
        intermediateButton->setText(QCoreApplication::translate("MainWindow", "INTERMEDIATE", nullptr));
        expertButton->setText(QCoreApplication::translate("MainWindow", "EXPERT", nullptr));
        customButton->setText(QCoreApplication::translate("MainWindow", "CUSTOM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MINESWEEPER_UI_H
