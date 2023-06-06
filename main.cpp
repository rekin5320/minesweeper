#include <iostream>
#include "game.hpp"

int main(int argc, char **argv)
{
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);
    QMainWindow window;

    Game game;
    game.setupUi(window);

    window.show();

    return app.exec();
}
