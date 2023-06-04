#include <iostream>
#include "logic.hpp"


int main(int argc, char **argv)
{
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);
    QMainWindow window;

    Game game{EXPERT};
    game.setupUi(window);
    game.start();
    game.create_tiles();

    window.show();

    return app.exec();
}
