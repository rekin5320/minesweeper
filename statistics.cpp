#include <iostream>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include "statistics.hpp"

QString get_data_dir()
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!QDir().mkpath(dataDir))
    {
        std::cerr << "Error when trying to create data directory: " << dataDir.toStdString() << "\n";
        exit(1);
    }
    return dataDir;
}

QString get_file_path()
{
    return get_data_dir() + "/data.json";
}

void save_game_result(Difficulty difficulty, int game_time_seconds, unsigned int width, unsigned int height, unsigned int num_bombs)
{
    /*
     * File has following structure:
     * {
     *     "history": [
     *         {…},
     *         {…},
     *         {…}
     *     ],
     *
     *     "highscores": {
     *         "0": …,
     *         "1": …,
     *         "2": …
     *     }
     * }
     */

    QString filePath = get_file_path();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        std::cerr << "Failed to open file for writing: " << file.errorString().toStdString() << "\n";
        exit(1);
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData);

    QJsonObject gameResultEntry;
    gameResultEntry["difficulty"] = difficulty; // save enum value
    if (difficulty == CUSTOM)
    {
        gameResultEntry["width"] = static_cast<int>(width);
        gameResultEntry["height"] = static_cast<int>(height);
        gameResultEntry["bombs"] = static_cast<int>(num_bombs);
    }
    gameResultEntry["time"] = static_cast<int>(game_time_seconds);

    QJsonObject jsonGameData;
    if (jsonDocument.isObject()) {
        jsonGameData = jsonDocument.object();
    }

    QJsonArray historyArray;
    if (jsonGameData.contains("history")) {
        QJsonValue historyValue = jsonGameData.value("history");
        historyArray = historyValue.toArray();
    }
    historyArray.append(gameResultEntry);

    QJsonObject highscoresObject;
    if (jsonGameData.contains("highscores"))
    {
        QJsonValue highscoresValue = jsonGameData.value("highscores");
        highscoresObject = highscoresValue.toObject();
    }

    QString difficulty_key = QString::number(static_cast<int>(difficulty));
    if (highscoresObject.contains(difficulty_key))
    { // choose lower time if highscore exists
        int difficulty_highscore = highscoresObject.value(difficulty_key).toInt();
        if (game_time_seconds < difficulty_highscore)
        {
            highscoresObject[difficulty_key] = game_time_seconds;
        }
    }
    else
    {
        highscoresObject[difficulty_key] = game_time_seconds;
    }

    QJsonObject outGameData;
    outGameData["history"] = historyArray;
    outGameData["highscores"] = highscoresObject;

    QJsonDocument outJsonDocument;
    outJsonDocument.setObject(outGameData);

    file.resize(0);
    file.write(outJsonDocument.toJson());
    file.close();
}

std::vector<int> get_highscores()
{
    QString filePath = get_file_path();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed to open file for reading: " << file.errorString().toStdString() << "\n";
        exit(1);
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData);

    QJsonObject jsonGameData;
    if (jsonDocument.isObject()) {
        jsonGameData = jsonDocument.object();
    }

    QJsonObject highscoresObject;
    if (jsonGameData.contains("highscores"))
    {
        QJsonValue highscoresValue = jsonGameData.value("highscores");
        highscoresObject = highscoresValue.toObject();
    }

    std::vector<int> highscores;
    for (auto difficulty_key : {"0", "1", "2"})
    {
        if (highscoresObject.contains(difficulty_key))
        {
            int difficulty_highscore = highscoresObject.value(difficulty_key).toInt();
            highscores.push_back(difficulty_highscore);
        }
        else {
            highscores.push_back(-1);
        }
    }

    return highscores;
}
