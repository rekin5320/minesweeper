#include <iostream>
#include <QtWidgets/QPushButton>

#include "minesweeper_ui.hpp"
#include "logic.hpp"


class GameUI: public Ui::MainWindow {
public:
    Game& game;
    std::vector<QPushButton*> buttons;

    GameUI(Game& game): game(game) {};

    void create_tiles(Board& board) {
        for (auto& tile : board.Tiles) {
            auto *button = new QPushButton();
            buttons.push_back(button);
            unsigned int x = tile.x, y = tile.y;
            QApplication::connect(button, &QPushButton::released, [this, x, y](){this->click_button(x, y);});
            gridLayout->addWidget(button, tile.y, tile.x);
        }
    };

    void click_button(unsigned int x, unsigned int y) {
        std::cout << x << " " << y << "\n";
        buttons[y * game.board.WIDTH + x]->setText("C");
    }
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
