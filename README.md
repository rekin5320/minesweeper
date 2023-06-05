# Minesweeper
Work in progress...

[![Github Releases](https://img.shields.io/badge/release-v1.0-brightgreen)](https://gitlab-stud.elka.pw.edu.pl/mmachnik/minesweeper)

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

## Credits
This project uses the following libraries:

* [Qt](https://www.qt.io/) ([LGPLv3 license](https://www.gnu.org/licenses/lgpl-3.0.en.html))
* [Catch2](https://github.com/catchorg/Catch2) ([BSL-1.0 license](https://github.com/catchorg/Catch2/blob/devel/LICENSE.txt))

The logo used in this project comes from [textcraft](https://textcraft.net) and [is licensed free of charge for commercial or non-commercial use](https://textcraft.net/privacy.php).

The background image used in this project is from [RareGALLERY](https://rare-gallery.com) and is licensed free of charge for commercial or non-commercial use.

## License
[GNU GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.html)
