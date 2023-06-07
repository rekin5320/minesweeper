<div align="center">
  <img src="resources/images/MINESWEEPER.png" alt="Minesweeper logo">
</div>

[![Github Releases](https://img.shields.io/badge/release-v1.0-brightgreen)](https://gitlab-stud.elka.pw.edu.pl/mmachnik/minesweeper)

## Game description
Minesweeper is a classic single-player puzzle game where the objective is to clear a board containing hidden mines without detonating any of them. Each cell can either be empty or contain a mine. The player's goal is to uncover all the empty cells without uncovering any mines. Uncovering a mine results in a game over.

### Gameplay
The game starts with a board of covered cells. The player can uncover a cell by clicking on it. If the clicked cell contains a mine, the game ends. Otherwise, the cell is uncovered, and it reveals a number indicating the number of adjacent cells that contain mines. The player can then use this information to deduce the location of the mines and continue uncovering more cells. The game is won when all the non-mine cells are uncovered.

### Controls
- Left click on tile: uncover (default) or flag (depending on selected tool)
- Right click on tile: flag or unflag
- Click on the button with a pickaxe icon: start uncovering cells with left click
- Click on the button with a flag icon: start flagging cells with left click
- Click on the button with an emoji icon: play again

### Difficulty Levels
The game offers following difficulty levels:

- Beginner: 9×9 board with 10 mines
- Intermediate: 16×16 board with 40 mines
- Expert: 16×30 board with 99 mines
- Custom: allows the player to customize the board size and number of mines (board size must be greater than 4×4 and the number of mines can be at most 50% of the total number of cells)

### Features
- Graphical user interface: the game provides a user-friendly GUI
- Timer: the game tracks the elapsed time during gameplay
- Flagging: the player can flag cells suspected to contain mines to keep track of them.
- Customizable game settings: the player can choose a custom board size and number of mines
- Saving game results and highscores: the game saves the elapsed time after winning a game

### How to Play
1. Launch the game with `./minesweeper`
2. Choose a difficulty level or use custom settings
3. Click on a cell using pickaxe tool to uncover it
4. Use the numbers revealed to deduce the location of mines
5. Click on a cell using flag tool to flag or unflag it as a potential mine
6. Continue uncovering cells and flagging potential mines until all non-mine cells are uncovered
7. If you uncover a mine, the game ends; if you uncover all non-mine cells, you win

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
cmake --build . -j$(nproc) --target minesweeper
```

## Running tests
```sh
mkdir build
cd build
cmake ..
cmake --build . -j$(nproc) --target test
./test
```

## Regenerating UI `.hpp` file after modifications in Qt Designer
```sh
uic minesweeper_ui.ui -o minesweeper_ui.hpp
```

## Credits
This project uses the following libraries:

- [Qt](https://www.qt.io/) ([LGPLv3 license](https://www.gnu.org/licenses/lgpl-3.0.en.html))
- [Catch2](https://github.com/catchorg/Catch2) ([BSL-1.0 license](https://github.com/catchorg/Catch2/blob/devel/LICENSE.txt))

The logo used in this project comes from [textcraft](https://textcraft.net) and [is licensed free of charge for commercial or non-commercial use](https://textcraft.net/privacy.php).

The background image used in this project is from [RareGALLERY](https://rare-gallery.com) and is licensed free of charge for commercial or non-commercial use.

## License
[GNU GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.html)
