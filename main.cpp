#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QtCore>
#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);

    QLabel hello("Hello world!");

    hello.show();

    return app.exec();
}

// g++ $(pkg-config --cflags --libs Qt5Widgets) -fPIC main.cpp -o main
// g++ $(pkg-config --cflags Qt5Widgets) -fPIC main.cpp -o main $(pkg-config --libs Qt5Widgets)