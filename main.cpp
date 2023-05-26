#include <QApplication>
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
