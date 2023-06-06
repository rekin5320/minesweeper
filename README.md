<div align="center">
  <img src="resources/images/MINESWEEPER.png" alt="Minesweeper logo">
</div>

[![Github Releases](https://img.shields.io/badge/release-v1.0-brightgreen)](https://gitlab-stud.elka.pw.edu.pl/mmachnik/minesweeper)

# Game Description
Minesweeper is a classic single-player puzzle game where the objective is to clear a rectangular grid containing hidden mines without detonating any of them. The grid is divided into cells, and each cell can either be empty or contain a mine. The player's goal is to uncover all the empty cells without uncovering any mines. Uncovering a mine results in a game over.

## Gameplay
The game starts with a grid of covered cells. The player can uncover a cell by clicking on it. If the clicked cell contains a mine, the game ends. Otherwise, the cell is uncovered, and it reveals a number indicating the number of adjacent cells that contain mines. The player can then use this information to deduce the location of the mines and continue uncovering more cells. The game is won when all the non-mine cells are uncovered.

## Controls
 - Click on picaxe icon: Start uncovering cells
 - Click on flag icon: Start flagging cells
 - Click on emoji icon: Play again

## Difficulty Levels
The game offers different difficulty levels:
 - Beginner: A 9x9 grid with 10 mines
 - Intermediate: A 16x16 grid with 40 mines
 - Expert: A 16x30 grid with 99 mines
 - Custom: Allows the player to customize the grid size and number of mines. Grid size must be greater than 4x4, and the number of mines can be maximum 50% of the total number of cells.

## Features
 - Graphical user interface: The game provides a user-friendly GUI for playing Minesweeper.
 - Timer: The game tracks the elapsed time during gameplay.
 - Flagging: The player can flag cells suspected to contain mines to keep track of them.
 - Customizable grid: The player can choose a custom grid size and number of mines.
 - Saving game results: The game saves the difficulty level, and elapsed time after winning a game.

## How to Play
1. Launch the game with `./minesweeper`.
2. Choose a difficulty level or customize the grid.
3. Click on a cell using pixaxe tool to uncover it.
4. Use the numbers revealed to deduce the location of mines.
5. Click on a cell using flag tool to flag or unflag it as a potential mine.
6. Continue uncovering cells and flagging potential mines until all non-mine cells are uncovered.
7. If you uncover a mine, the game ends. If you uncover all non-mine cells, you win.

Enjoy playing Minesweeper and have fun!

## Requirements
- C++20 compiler
- Qt5
- CMake
- system font capable of displaying emojis (on Ubuntu such font can be installed with `sudo apt-get install fonts-noto-color-emoji`)

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

## Regenerating UI `.hpp` file after modifications in Qt Designer
```sh
uic-qt5 minesweeperUI.ui -o minesweeperUI.hpp
```

## Credits
This project uses the following libraries:

- [Qt](https://www.qt.io/) ([LGPLv3 license](https://www.gnu.org/licenses/lgpl-3.0.en.html))
- [Catch2](https://github.com/catchorg/Catch2) ([BSL-1.0 license](https://github.com/catchorg/Catch2/blob/devel/LICENSE.txt))

The logo used in this project comes from [textcraft](https://textcraft.net) and [is licensed free of charge for commercial or non-commercial use](https://textcraft.net/privacy.php).

The background image used in this project is from [RareGALLERY](https://rare-gallery.com) and is licensed free of charge for commercial or non-commercial use.

## License
[GNU GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.html)
