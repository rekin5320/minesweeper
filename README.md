# Minesweeper
Work in progress...

## Building
```sh
mkdir build
cd build
cmake ..
make minesweeper
```

## Regenerating UI `.hpp` file after modifications in Qt Designer
```sh
uic-qt5 minesweeperUI.ui -o minesweeperUI.hpp
```

## Note about font for emojis
A system font capable of displaying emojis is required. On Ubuntu such font can be installed with:

```sh
sudo apt-get install fonts-noto-color-emoji
```
