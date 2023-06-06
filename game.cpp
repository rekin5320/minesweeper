#include <iomanip>
#include "game.hpp"


void Game::set_level(Difficulty difficulty_to_set, unsigned int width, unsigned int height, unsigned int bombs) {
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
                throw std::invalid_argument("Missing parameters for custom level");
            }
            board = Board(width, height);
            num_bombs = bombs;
            difficulty = CUSTOM;
            break;
        default:
            throw std::invalid_argument("Invalid difficulty");
    }
}

void Game::start() {
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

void Game::play_again() {
    if (has_started)
    {
        board.clear_bombs();
        board.unflag_all();
        board.cover_all();
        start();
        if (with_gui)
        {
            ui.mainbutton->setText("🙂");
        }
    }
}

void Game::setupUi(QMainWindow& MainWindow) {
    ui.setupUi(&MainWindow);
    QObject::connect(ui.beginnerButton, &QPushButton::released, [this]()
    {
        set_level(BEGINNER);
        start();
        create_tiles(); });
    QObject::connect(ui.intermediateButton, &QPushButton::released, [this]()
    {
        set_level(INTERMEDIATE);
        start();
        create_tiles(); });
    QObject::connect(ui.expertButton, &QPushButton::released, [this]()
    {
        set_level(EXPERT);
        start();
        create_tiles(); });
    QObject::connect(ui.customButton, &QPushButton::released, [this]()
    {
        unsigned int width;
        unsigned int height;
        unsigned int bombs;
        std::cout << "Enter width: ";
        std::cin >> width;
        std::cout << "Enter height: ";
        std::cin >> height;
        std::cout << "Enter bombs: ";
        std::cin >> bombs;
        set_level(CUSTOM, width, height, bombs);
        start();
        create_tiles(); });
    QObject::connect(ui.mainbutton, &QPushButton::released, [this](){play_again(); });
    QObject::connect(ui.uncoverButton, &QPushButton::released, [this](){set_tool_uncover(); });
    QObject::connect(ui.flagButton, &QPushButton::released, [this](){set_tool_flag(); });
    QObject::connect(&timer, &QTimer::timeout, [this](){update_timer(); });
    with_gui = true;
    set_tool_uncover();
}

void Game::create_tiles() {
    for (auto &tile : board.Tiles)
    {
        unsigned int x = tile.x, y = tile.y;
        tile.create_button();
        ui.gridLayout->addWidget(tile.button.get(), static_cast<int>(y), static_cast<int>(x));
        tile.button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        QObject::connect(tile.button.get(), &QPushButton::released, [this, x, y]()
        {
            if (tool == UNCOVER)
            {
                uncover_tile(x, y);
            }
            else if (tool == FLAG)
            {
                if (!first_click)
                {
                    flag_or_unflag_tile(x, y);
                }
            } });
    }
}

void Game::set_tool_uncover() {
    tool = UNCOVER;
    if (with_gui)
    {
        ui.uncoverButton->setEnabled(false);
        ui.flagButton->setEnabled(true);
    }
}

void Game::set_tool_flag() {
    tool = FLAG;
    if (with_gui)
    {
        ui.uncoverButton->setEnabled(true);
        ui.flagButton->setEnabled(false);
    }
}

void Game::update_bombs_left() {
    ui.lcdNumber_left->display(static_cast<int>(left_bombs()));
}

void Game::update_timer() {
    if (!first_click && !has_ended)
    {
        ui.lcdNumber_right->display(++game_time_seconds);
    }
}

void Game::uncover_tile(unsigned int x, unsigned int y) {
    if (first_click)
    {
        while ((board.get_tile(x, y).is_bomb || board.get_tile(x, y).num_adjacent_bombs > 0))
        { // regenerate bombs to ensure safe first click
            board.clear_bombs();
            board.generate_bombs(num_bombs);
            board.count_adjacent_bombs();
        }
        if (with_gui) {
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
            std::cout << "Game over! You lost the game in: " << get_formatted_elapsed_time() << "!\n";
            if (with_gui)
            {
                ui.mainbutton->setText("🙁");
            }
        }
        else if (is_game_won())
        {
            has_ended = true;
            std::cout << "Congratulations! You won the game in: " << get_formatted_elapsed_time() << "!\n";
            if (with_gui)
            {
                ui.mainbutton->setText("😎");
            }
        }
    }
}

void Game::flag_or_unflag_tile(unsigned int x, unsigned int y) {
    board.flag_or_unflag_tile(x, y);
    update_bombs_left();
}

int Game::left_bombs() {
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

bool Game::is_game_over() {
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

bool Game::is_game_won() {
    for (auto &tile : board.Tiles)
    {
        if (!tile.is_bomb && tile.is_covered)
        {
            return false;
        }
    }
    save_game_result();
    return true;
}

std::string Game::get_formatted_elapsed_time() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << game_time_seconds / 60 << ":";
    oss << std::setfill('0') << std::setw(2) << game_time_seconds % 60;
    return oss.str();
}

QString Game::difficultyToString(Difficulty difficulty_input) {
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

void Game::save_game_result() const {
    QDir dir;
    if (!dir.exists(QStandardPaths::writableLocation(QStandardPaths::DataLocation)))
        dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));

    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/game_results.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData);

    QJsonObject gameResult;

    gameResult["level"] = difficultyToString(difficulty);

    if (difficulty == CUSTOM)
    {
        gameResult["width"] = static_cast<int>(board.width);
        gameResult["height"] = static_cast<int>(board.height);
        gameResult["bombs"] = static_cast<int>(num_bombs);
    }

    gameResult["time"] = static_cast<int>(game_time_seconds);

    QJsonArray gameResultsArray;
    if (jsonDocument.isArray())
    {
        gameResultsArray = jsonDocument.array();
    }
    gameResultsArray.append(gameResult);

    QJsonDocument newJsonDocument(gameResultsArray);

    file.resize(0);
    file.write(newJsonDocument.toJson());
    file.close();
}
