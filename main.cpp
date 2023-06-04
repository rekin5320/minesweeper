#include <iostream>
#include "logic.hpp"
#include "minesweeper_ui.hpp"

class GameUI : public Ui::MainWindow
{
public:
    Game &game;

    GameUI(Game &game) : game(game){};

    void create_tiles(Board &board)
    {
        for (auto &tile : board.Tiles)
        {
            unsigned int x = tile.x, y = tile.y;
            tile.create_button();
            gridLayout->addWidget(tile.button.get(), y, x);
            tile.button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            QObject::connect(tile.button.get(), &QPushButton::released, [&board, x, y](){board.uncover_tile(x, y);});
        }
    };
};

int main(int argc, char **argv)
{
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);

    QMainWindow window;
    Game game{EXPERT};
    GameUI ui{game};
    ui.setupUi(&window);
    game.start();
    ui.create_tiles(game.board);

    window.show();

    while (!game.is_game_over() && !game.is_game_won())
    {
        app.processEvents();
    }

    if (game.is_game_won())
    {
        std::cout << "Congratulations! You won the game in: " << game.get_formatted_elapsed_time() << "!" << std::endl;
    }
    else
    {
        std::cout << "Game over! You lost the game in: " << game.get_formatted_elapsed_time() << "!"<< std::endl;
    }

    return app.exec();
}
