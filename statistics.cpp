#include <iostream>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include "statistics.hpp"

const QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

const QString filePath = dataDir + "/game_results.json";

void ensure_data_dir_exists()
{
    if (!QDir().mkpath(dataDir))
    {
        std::cerr << "Error when trying to create data directory: " << dataDir.toStdString() << "\n";
        exit(1);
    }
}

void save_game_result(Difficulty difficulty, unsigned int game_time_seconds, unsigned int width, unsigned int height, unsigned int num_bombs)
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

    ensure_data_dir_exists();

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
        if (historyValue.isArray()) {
            historyArray = historyValue.toArray();
        }
    }
    historyArray.append(gameResultEntry);

    QJsonObject highscoresObject;
    if (jsonGameData.contains("highscores"))
    {
        QJsonValue highscoresValue = jsonGameData.value("highscores");
        if (highscoresValue.isObject())
        {
            highscoresObject = highscoresValue.toObject();
        }
    }

    highscoresObject[QString::number(static_cast<int>(difficulty))] = static_cast<int>(game_time_seconds);  // TODO choose lower time

    QJsonObject outGameData;
    outGameData["history"] = historyArray;
    outGameData["highscores"] = highscoresObject;

    QJsonDocument outJsonDocument;
    outJsonDocument.setObject(outGameData);

    file.resize(0);
    file.write(outJsonDocument.toJson());
    file.close();
}
