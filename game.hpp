#pragma once
#include <QTimer>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include "position.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "difficulty.hpp"
#include "minesweeper_ui.hpp"

enum Tool
{
    FLAG,
    UNCOVER
};

class Game
{
private:
    Board board;
    unsigned int num_bombs;
    bool with_gui;
    bool has_ended;
    bool has_started = false;
    bool first_click;
    Ui::MainWindow ui;
    int game_time_seconds;
    QTimer timer{};
    Tool tool = UNCOVER;
    Difficulty difficulty;

public:
    // constructor
    Game() : with_gui(false) {}

    // Getters
    Board &get_board();

    unsigned int get_num_bombs() const;

    bool get_with_gui() const;

    bool get_has_ended() const;

    bool get_has_started() const;

    bool get_first_click() const;

    Ui::MainWindow &get_ui();

    int get_game_time_seconds() const;

    Tool get_tool() const;

    Difficulty get_difficulty() const;

    // Setters
    void set_difficulty(
        Difficulty difficulty_to_set,
        unsigned int width = 0,
        unsigned int height = 0,
        unsigned int bombs = 0);

    void set_tool_uncover();

    void set_tool_flag();

    // Methods
    void start();

    void play_again();

    void setupUi(QMainWindow &MainWindow);

    void create_tiles();

    void update_bombs_left();

    void update_timer();

    void custom_difficulty_dialog(const QString &error_message = "");

    void uncover_tile(unsigned int x, unsigned int y);

    void flag_or_unflag_tile(unsigned int x, unsigned int y);

    int left_bombs();

    bool is_game_over();

    bool is_game_won();

    std::string get_formatted_elapsed_time() const;

    static QString difficultyToString(Difficulty difficulty_input);
};
