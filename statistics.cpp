#include <iostream>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include "difficulty.hpp"
#include "statistics.hpp"

void save_game_result(Difficulty difficulty, unsigned int game_time_seconds, unsigned int width, unsigned int height, unsigned int num_bombs)
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!QDir().mkpath(dataDir))
    {
        std::cerr << "Error when trying to create data directory: " << dataDir.toStdString() << "\n";
        return;
    }

    QString filePath = dataDir + "/game_results.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        std::cerr << "Failed to open file for writing: " << file.errorString().toStdString() << "\n";
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData);

    QJsonObject gameResult;

    gameResult["difficulty"] = difficulty; // save enum value

    if (difficulty == CUSTOM)
    {
        gameResult["width"] = static_cast<int>(width);
        gameResult["height"] = static_cast<int>(height);
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
