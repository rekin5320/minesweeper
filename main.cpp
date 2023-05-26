#include <QApplication>
#include <QLabel>
#include <QtCore>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>


int main(int argc, char **argv) {
    std::cout << "Qt version: " << qVersion() << std::endl;

    QApplication app(argc, argv);

    QWidget window{};

    QLabel label{"Hello, world!"};
    QPushButton button{"Click"};
    QApplication::connect(&button, &QPushButton::released, [&label](){label.setText("changed");});

    QHBoxLayout layout{};
    layout.addWidget(&label);
    layout.addWidget(&button);
    window.setLayout(&layout);

    window.show();

    return app.exec();
}
