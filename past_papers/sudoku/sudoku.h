#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

/* Main functions */

bool is_complete(char board[9][9]);

bool make_move(const char position[],const char digit,char board[9][9]);

bool save_board(const char* filename, char board[9][9]);

bool solve_board(char board[9][9]);


void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
