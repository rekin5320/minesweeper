#pragma once
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QTimer>
#include "position.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "minesweeper_ui.hpp"


enum Difficulty
{
    BEGINNER,
    INTERMEDIATE,
    EXPERT,
    CUSTOM
};

enum Tool
{
    FLAG,
    UNCOVER
};

class Game
{
public:
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

    Game() : with_gui(false) {}

    void set_level(Difficulty difficulty_to_set, unsigned int width = 0, unsigned int height = 0, unsigned int bombs = 0);

    void start();

    void play_again();

    void setupUi(QMainWindow &MainWindow);

    void create_tiles();

    void set_tool_uncover();

    void set_tool_flag();

    void update_bombs_left();

    void update_timer();

    void uncover_tile(unsigned int x, unsigned int y);

    void flag_or_unflag_tile(unsigned int x, unsigned int y);

    int left_bombs();

    bool is_game_over();

    bool is_game_won();

    std::string get_formatted_elapsed_time() const;

    static QString difficultyToString(Difficulty difficulty_input);

    void save_game_result() const;
};
