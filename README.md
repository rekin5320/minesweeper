# Minesweeper
Work in progress...

## Building
```sh
mkdir build
cd build
cmake ..
make
```

## Regenerating UI `.hpp` file after modifications in Qt Designer
```sh
uic-qt5 minesweeperUI.ui -o minesweeperUI.hpp
```
