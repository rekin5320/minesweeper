#include <iostream>
#include "minesweeper_ui.hpp"
#include "logic.hpp"


class GameUI: public Ui::MainWindow {
public:
    Game& game;

    GameUI(Game& game): game(game) {};

    void create_tiles(Board& board) {
        for (auto& tile : board.Tiles) {
            tile.button = std::make_shared<QPushButton>();
            QApplication::connect(tile.button.get(), &QPushButton::released, [&tile](){tile.click_button();});
            gridLayout->addWidget(tile.button.get(), tile.y, tile.x);
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
