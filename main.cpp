#include <iostream>
#include <QtWidgets/QPushButton>

#include "minesweeper_ui.hpp"
#include "logic.hpp"


class GameUI: public Ui::MainWindow {
public:
    void create_tiles(Board& board) {
        for (auto& tile : board.Tiles) {
            auto *button = new QPushButton();
            QApplication::connect(button, &QPushButton::released, [this](){this->label->setText("changed");});
            gridLayout->addWidget(button, tile.y, tile.x);
        }
    };
};


int main(int argc, char **argv) {
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);
    QMainWindow window;
    GameUI ui;
    ui.setupUi(&window);
    Board board{15, 10};
    ui.create_tiles(board);

    // QApplication::connect(ui.button, &QPushButton::released, [&ui](){ui.label->setText("changed");});

    window.show();
    return app.exec();
}
