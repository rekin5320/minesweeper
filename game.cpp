#include "emoji.hpp"
#include "statistics.hpp"
#include "game.hpp"

// Getters
Board &Game::get_board()
{
    return board;
}

unsigned int Game::get_num_bombs() const
{
    return num_bombs;
}

bool Game::get_with_gui() const
{
    return with_gui;
}

bool Game::get_has_ended() const
{
    return has_ended;
}

bool Game::get_has_started() const
{
    return has_started;
}

bool Game::get_first_click() const
{
    return first_click;
}

Ui::MainWindow &Game::get_ui()
{
    return ui;
}

int Game::get_game_time_seconds() const
{
    return game_time_seconds;
}

Tool Game::get_tool() const
{
    return tool;
}

Difficulty Game::get_difficulty() const
{
    return difficulty;
}

void Game::set_difficulty(Difficulty difficulty_to_set, unsigned int width, unsigned int height, unsigned int bombs)
{
    switch (difficulty_to_set)
    {
    case BEGINNER:
        board = Board(9, 9);
        num_bombs = 10;
        difficulty = BEGINNER;
        break;
    case INTERMEDIATE:
        board = Board(16, 16);
        num_bombs = 40;
        difficulty = INTERMEDIATE;
        break;
    case EXPERT:
        board = Board(30, 16);
        num_bombs = 99;
        difficulty = EXPERT;
        break;
    case CUSTOM:
        if (width == 0 || height == 0 || bombs == 0)
        {
            throw std::invalid_argument("Invalid parameters for custom difficulty");
        }
        board = Board(width, height);
        num_bombs = bombs;
        difficulty = CUSTOM;
        break;
    default:
        throw std::invalid_argument("Invalid difficulty");
    }
}

void Game::set_tool_uncover()
{
    tool = UNCOVER;
    if (with_gui)
    {
        ui.uncoverButton->setEnabled(false);
        ui.flagButton->setEnabled(true);
    }
}

void Game::set_tool_flag()
{
    tool = FLAG;
    if (with_gui)
    {
        ui.uncoverButton->setEnabled(true);
        ui.flagButton->setEnabled(false);
    }
}

void Game::start()
{
    has_ended = false;
    has_started = true;
    first_click = true;
    board.generate_bombs(num_bombs);
    board.count_adjacent_bombs();
    game_time_seconds = 0;
    if (with_gui)
    {
        update_bombs_left();
        ui.lcdNumber_right->display(0);
    }
}

void Game::play_again()
{
    if (has_started)
    {
        board.clear_bombs();
        board.unflag_all();
        board.cover_all();
        start();
        if (with_gui)
        {
            ui.mainbutton->setText(Emoji::SmileyFace);
        }
    }
}

void Game::setupUi(QMainWindow &MainWindow)
{
    ui.setupUi(&MainWindow);
    QObject::connect(ui.beginnerButton, &QPushButton::released, [this]()
                     {
        set_difficulty(BEGINNER);
        start();
        create_tiles(); });
    QObject::connect(ui.intermediateButton, &QPushButton::released, [this]()
                     {
        set_difficulty(INTERMEDIATE);
        start();
        create_tiles(); });
    QObject::connect(ui.expertButton, &QPushButton::released, [this]()
                     {
        set_difficulty(EXPERT);
        start();
        create_tiles(); });
    QObject::connect(ui.customButton, &QPushButton::released, [this]()
                     { custom_difficulty_dialog(); });
    QObject::connect(ui.mainbutton, &QPushButton::released, [this]()
                     { play_again(); });
    QObject::connect(ui.uncoverButton, &QPushButton::released, [this]()
                     { set_tool_uncover(); });
    QObject::connect(ui.flagButton, &QPushButton::released, [this]()
                     { set_tool_flag(); });
    QObject::connect(ui.statisticsButton, &QPushButton::released, [this](){statistics_window();});
    QObject::connect(&timer, &QTimer::timeout, [this]()
                     { update_timer(); });
    with_gui = true;
    set_tool_uncover();
}

void Game::create_tiles()
{
    for (auto &tile : board.Tiles)
    {
        unsigned int x = tile.x, y = tile.y;
        tile.create_button();
        ui.gridLayout->addWidget(tile.button.get(), static_cast<int>(y), static_cast<int>(x));
        tile.button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        QObject::connect(tile.button.get(), &MyButton::leftButtonClicked, [this, x, y]()
                         {
            if (tool == UNCOVER)
            {
                uncover_tile(x, y);
            }
            else if (tool == FLAG)
            {
                flag_or_unflag_tile(x, y);
            } });
        QObject::connect(tile.button.get(), &MyButton::rightButtonClicked, [this, x, y](){flag_or_unflag_tile(x, y);});
    }
}

void Game::update_bombs_left()
{
    ui.lcdNumber_left->display(static_cast<int>(left_bombs()));
}

void Game::update_timer()
{
    if (!first_click && !has_ended)
    {
        ui.lcdNumber_right->display(++game_time_seconds);
    }
}

void Game::custom_difficulty_dialog(const QString &error_message)
{
    QDialog dialog;
    QFormLayout formLayout(&dialog);
    QLabel label;
    QLineEdit widthLineEdit;
    QLineEdit heightLineEdit;
    QLineEdit bombsLineEdit;
    QPushButton startButton("Start");

    if (error_message.length())
    {
        label.setText(error_message);
        formLayout.addRow("Error:", &label);
    }
    formLayout.addRow("Width:", &widthLineEdit);
    formLayout.addRow("Height:", &heightLineEdit);
    formLayout.addRow("Bombs:", &bombsLineEdit);
    formLayout.addWidget(&startButton);

    QObject::connect(&startButton, &QPushButton::released, [&]()
                     {
        dialog.close();

        unsigned int width = widthLineEdit.text().toUInt();
        unsigned int height = heightLineEdit.text().toUInt();
        unsigned int bombs = bombsLineEdit.text().toUInt();

        try
        {
            set_difficulty(CUSTOM, width, height, bombs);
            start();
            create_tiles();
        }
        catch (std::invalid_argument& e)
        {
            custom_difficulty_dialog(e.what()); // ask user again if entered parameters were invalid
        } });

    dialog.setLayout(&formLayout);
    dialog.setWindowTitle("Custom parameters");
    dialog.exec();
}

void Game::uncover_tile(unsigned int x, unsigned int y)
{
    if (first_click)
    {
        while ((board.get_tile(x, y).is_bomb || board.get_tile(x, y).num_adjacent_bombs > 0))
        { // regenerate bombs to ensure safe first click
            board.clear_bombs();
            board.generate_bombs(num_bombs);
            board.count_adjacent_bombs();
        }
        if (with_gui)
        {
            timer.start(1000); // update every 1000 milliseconds (1 second)}
        }
        first_click = false;
    }

    if (!has_ended)
    {
        board.uncover_tile(x, y);
        if (is_game_over())
        {
            has_ended = true;
            std::cout << "Game over! You lost the game in: " << get_formatted_time(game_time_seconds) << "!\n";
            if (with_gui)
            {
                ui.mainbutton->setText(Emoji::SadFace);
            }
        }
        else if (is_game_won())
        {
            has_ended = true;
            std::cout << "Congratulations! You won the game in: " << get_formatted_time(game_time_seconds) << "!\n";
            if (with_gui)
            {
                ui.mainbutton->setText(Emoji::CoolFace);
            }
        }
    }
}

void Game::flag_or_unflag_tile(unsigned int x, unsigned int y)
{
    if (!first_click)
    {
        board.flag_or_unflag_tile(x, y);
        update_bombs_left();
    }
}

int Game::left_bombs()
{
    int count = static_cast<int>(num_bombs);
    for (auto &tile : board.Tiles)
    {
        if (tile.is_flagged)
        {
            count--;
        }
    }
    return count;
}

bool Game::is_game_over()
{
    for (auto &tile : board.Tiles)
    {
        if (tile.is_bomb && !tile.is_covered)
        {
            board.uncover_bombs();
            return true;
        }
    }
    return false;
}

bool Game::is_game_won()
{
    for (auto &tile : board.Tiles)
    {
        if (!tile.is_bomb && tile.is_covered)
        {
            return false;
        }
    }
    save_game_result(difficulty, game_time_seconds, board.width, board.height, num_bombs);
    return true;
}

void Game::statistics_window() {
    QDialog dialog;
    QFormLayout formLayout(&dialog);
    QLabel blank, label_beginner, label_intermediate, label_expert;

    auto highscores = get_highscores();
    if (highscores[0] > 0) {
        label_beginner.setText(QString::fromStdString(get_formatted_time(highscores[0])));
    }
    else {
        label_beginner.setText("none");
    }
    if (highscores[1] > 0) {
        label_intermediate.setText(QString::fromStdString(get_formatted_time(highscores[1])));
    }
    else {
        label_intermediate.setText("none");
    }
    if (highscores[2] > 0) {
        label_expert.setText(QString::fromStdString(get_formatted_time(highscores[2])));
    }
    else {
        label_expert.setText("none");
    }

    formLayout.addRow("HIGHSCORES", &blank);
    formLayout.addRow("Beginner:", &label_beginner);
    formLayout.addRow("Intermediate:", &label_intermediate);
    formLayout.addRow("Expert:", &label_expert);

    dialog.setLayout(&formLayout);
    dialog.setWindowTitle("Statistics");
    dialog.exec();
}

QString Game::difficultyToString(Difficulty difficulty_input)
{
    switch (difficulty_input)
    {
    case BEGINNER:
        return "Beginner";
    case INTERMEDIATE:
        return "Intermediate";
    case EXPERT:
        return "Expert";
    case CUSTOM:
        return "Custom";
    default:
        return "Unknown";
    }
}
