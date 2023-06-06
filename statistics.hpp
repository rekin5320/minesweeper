#pragma once
#include "difficulty.hpp"

extern const QString dataDir;

extern const QString filePath;

void ensure_data_dir_exists();

void save_game_result(Difficulty difficulty, unsigned int game_time_seconds, unsigned int width = 0, unsigned int height = 0, unsigned int num_bombs = 0);