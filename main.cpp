#include <iostream>
#include "logic.hpp"
#include "minesweeper_ui.hpp"


class GameUI: public Ui::MainWindow {
public:
    Game& game;

    GameUI(Game& game): game(game) {};

    void create_tiles(Board& board) {
        for (auto& tile : board.Tiles) {
            unsigned int x = tile.x, y = tile.y;
            tile.create_button();
            gridLayout->addWidget(tile.button.get(), y, x);
            tile.button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            QApplication::connect(tile.button.get(), &QPushButton::released, [&board, x, y](){board.uncover_tile(x, y);});
        }
    };
};


int main(int argc, char **argv) {
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);

    QMainWindow window;
    Game game{INTERMEDIATE};
    GameUI ui{game};
    ui.setupUi(&window);
    game.start();
    ui.create_tiles(game.board);

    window.show();
    return app.exec();
}
