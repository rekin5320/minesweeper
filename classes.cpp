#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 10;
const int COLS = 10;
const int BOMBS = 15;

enum SquareState
{
    COVERED,
    UNCOVERED,
    FLAGGED
};

enum SquareValue
{
    EMPTY,
    BOMB
};

struct Square
{
    SquareState state;
    SquareValue value;
    int adjacent_bombs;
};

void print_board(vector<vector<Square>> &board)
{
    cout << "  ";
    for (int j = 0; j < COLS; j++)
    {
        cout << j << " ";
    }
    cout << endl;
    for (int i = 0; i < ROWS; i++)
    {
        cout << i << " ";
        for (int j = 0; j < COLS; j++)
        {
            Square square = board[i][j];
            if (square.state == COVERED)
            {
                cout << "* ";
            }
            else if (square.state == FLAGGED)
            {
                cout << "F ";
            }
            else if (square.value == BOMB)
            {
                cout << "X ";
            }
            else
            {
                cout << square.adjacent_bombs << " ";
            }
        }
        cout << endl;
    }
}

void place_bombs(vector<vector<Square>> &board, int num_bombs)
{
    int bombs_placed = 0;
    while (bombs_placed < num_bombs)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (board[row][col].value != BOMB)
        {
            board[row][col].value = BOMB;
            bombs_placed++;
        }
    }
}

void count_adjacent_bombs(vector<vector<Square>> &board)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j].value == EMPTY)
            {
                int count = 0;
                for (int ii = -1; ii <= 1; ii++)
                {
                    for (int jj = -1; jj <= 1; jj++)
                    {
                        if (i + ii >= 0 && i + ii < ROWS && j + jj >= 0 && j + jj < COLS)
                        {
                            if (board[i + ii][j + jj].value == BOMB)
                            {
                                count++;
                            }
                        }
                    }
                }
                board[i][j].adjacent_bombs = count;
            }
        }
    }
}

bool is_valid(int row, int col)
{
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

bool is_uncovered(vector<vector<Square>> &board, int row, int col)
{
    return board[row][col].state == UNCOVERED;
}

bool is_bomb(vector<vector<Square>> &board, int row, int col)
{
    return board[row][col].value == BOMB;
}

bool is_flagged(vector<vector<Square>> &board, int row, int col)
{
    return board[row][col].state == FLAGGED;
}

bool is_game_over(vector<vector<Square>> &board, int row, int col)
{
    if (is_bomb(board, row, col))
    {
        return true;
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (is_bomb(board, i, j) && is_uncovered(board, i, j))
            {
                return true;
            }
        }
    }
    return false;
}

void uncover_square(vector<vector<Square>> &board, int row, int col)
{
    if (is_valid(row, col) && !is_uncovered(board, row, col) && !is_flagged(board, row, col))
    {
        board[row][col].state = UNCOVERED;
        if (board[row][col].value == EMPTY)
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    uncover_square(board, row + i, col + j);
                }
            }
        }
    }
}

void flag_square(vector<vector<Square>> &board, int row, int col)
{
    if (is_valid(row, col) && !is_uncovered(board, row, col))
    {
        if (board[row][col].state == COVERED)
        {
            board[row][col].state = FLAGGED;
        }
        else if (board[row][col].state == FLAGGED)
        {
            board[row][col].state = COVERED;
        }
    }
}

int main()
{
    vector<vector<Square>> board(ROWS, vector<Square>(COLS, {COVERED, EMPTY, 0}));
    srand(time(NULL));
    place_bombs(board, BOMBS);
    count_adjacent_bombs(board);
    bool game_over = false;
    while (!game_over)
    {
        print_board(board);
        int row, col;
        cout << "Enter row and column: ";
        cin >> row >> col;
        char action;
        cout << "Enter action (u for uncover, f for flag): ";
        cin >> action;
        if (action == 'u')
        {
            if (is_bomb(board, row, col))
            {
                game_over = true;
            }
            else
            {
                uncover_square(board, row, col);
            }
        }
        else if (action == 'f')
        {
            flag_square(board, row, col);
        }
        game_over = game_over || is_game_over(board, row, col);
    }
    print_board(board);
    cout << "Game over!" << endl;
    return 0;
}


//  Ta implementacja tworzy planszę o wymiarach 10x10,
//  w której umieszczane jest 15 bomb.
//   Gracz może odkryć pola planszy lub oznaczyć je flagą.
//    Jeśli gracz odkryje pole z bombą, gra się kończy.
//     Jeśli gracz odkryje wszystkie pola bez bomb, wygrywa.
