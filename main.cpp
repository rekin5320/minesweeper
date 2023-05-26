#include <QApplication>
#include <QLabel>
#include <QtCore>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <iostream>
#include "minesweeperUI.hpp"


int main(int argc, char **argv) {
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);
    QMainWindow window;
    Ui::MainWindow ui;
    ui.setupUi(&window);

    QApplication::connect(ui.button, &QPushButton::released, [&ui](){ui.label->setText("changed");});

    window.show();
    return app.exec();
}
