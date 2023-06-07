#pragma once
#include <vector>
#include "difficulty.hpp"

QString get_data_dir();

QString get_file_path();

void save_game_result(Difficulty difficulty, int game_time_seconds, unsigned int width = 0, unsigned int height = 0, unsigned int num_bombs = 0);

std::vector<int> get_highscores();
