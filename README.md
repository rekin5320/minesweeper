# Minesweeper
Work in progress...

## Building
```sh
mkdir build
cd build
cmake ..
make minesweeper
```

## Running tests
```sh
mkdir build
cd build
cmake ..
make test
./test
```

## Note about font for emojis
A system font capable of displaying emojis is required. On Ubuntu such font can be installed with:

```sh
sudo apt-get install fonts-noto-color-emoji
```

## Regenerating UI `.hpp` file after modifications in Qt Designer
```sh
uic-qt5 minesweeperUI.ui -o minesweeperUI.hpp
```

## Usage terms
This project uses the following libraries:
* [Qt](https://www.qt.io/) - [LGPLv3](https://www.gnu.org/licenses/lgpl-3.0.en.html)
* [Catch2]

The logo used in this project is from [textcraft](https://textcraft.net) and is licensed by free for commercial or non-commercial use.

The background image used in this project is from [RareGALLERY](https://rare-gallery.com)and is licensed by free for commercial or non-commercial use.
