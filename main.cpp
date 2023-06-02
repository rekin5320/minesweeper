#include <iostream>

#include "minesweeper_ui.hpp"


int main(int argc, char **argv) {
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);
    QMainWindow window;
    Ui::MainWindow ui;
    ui.setupUi(&window);
    // program shuts down after resizing the window
    // window.setFixedSize(1080, 700);

    QApplication::connect(ui.button, &QPushButton::released, [&ui](){ui.label->setText("changed");});

    window.show();
    return app.exec();
}
