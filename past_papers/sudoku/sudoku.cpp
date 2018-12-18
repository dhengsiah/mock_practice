#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

bool is_complete(char board[9][9]){
	//Checks whether there are any "blanks"
	for(int i =0; i<9;i++){
		for(int j=0;j<9;j++){
			if(board[i][j] == '.'){
				return 0;
			}
		}
	}
	return 1;
}

bool make_move(const char position[], const char digit, char board[9][9]){
	//Board[i][j] : i takes the alphabet, j takes number

	//Extract the i value that the alphabet represents

	char check_row[] = "ABCDEFGHI";
	char check_col[] = "123456789";
	int row = -1;
	int col = -1;

	for(int i =0;i<(signed)strlen(check_row);i++){
		if(position[0] == check_row[i]){
			row = i;
		}
	}

	if(row == -1){
		cerr << "Invalid coordinate position" << endl;
		return 0;
	}
	
	for(int i =0;i<(signed)strlen(check_row);i++){
		if(position[1] == check_col[i]){
			col = i;
		}
	}
	
	if(col == -1){
		cerr << "Invalid coordinate position" << endl;
		return 0;
	}
	
	//Check whether input is "valid"

	//Check whether square is empty
	if(board[row][col] != '.'){
		return 0;
	}


	//First check the sub-board
	for(int i= (row/3)*3;i<(row/3)*3+3;i++){
		for(int j = (col/3)*3 ; j<(col/3)*3+3;j++){
			if(board[i][j] == digit){
				return 0;
			}
		}
	}

	//Check along the row
	for(int i = 0;i<9;i++){
		if(row != i && board[i][col] == digit){
			return 0;
		}
	}

	//Check along the col
	for(int i=0;i<9;i++){
		if(col !=i && board[row][i] == digit){
			return 0;
		}
	}
	
	board[row][col] = digit;
	return 1;
}

bool save_board(const char* filename, char board[9][9]){
	ofstream output;

	output.open(filename);
	if(output.fail()){
		cerr << "Error creating new file" << endl;
		return 0;
	}

	for(int i=0;i<9;i++){
		for(int j =0;j<9;j++){
			output.put(board[i][j]);
		}
			output.put('\n');
	}
	
	return 1;
}

bool solve_board(char board[9][9]){
	//Make a copy of board

	char board_copy[9][9];
	char position[3];

	for(int i = 0;i<9;i++){
		for(int j =0;j<9;j++){
			board_copy[i][j] = board[i][j];
		}
	}

	//Iterate through each square of the board
	if(is_complete(board)){
		return 1;
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			//Check whether square unfilled
			if(board[i][j] == '.'){
				//Convert to position
				position[0] = (char)i + 'A';
				position[1] = (char)j + '1';
				position[2] = '\0';

				//Iterate through each digit
				for(int k=0;k<9;k++){
//				cout << position << endl;
//				cout << k+1 << endl;
//				display_board(board_copy);
	
					if(make_move(position,(char)k+'1',board_copy)){
						//If move is valid,call solve_board again on the board + filled square
						if(solve_board(board_copy)){
							//If solve_board succeeds copy board_copy into board
							for(int l=0;l<9;l++){
								for(int m=0;m<9;m++){
									board[l][m] = board_copy[l][m];
								}
							}
							return 1;
						
						//If reach a point where we can't progress, revert board
						}else{
							for(int l=0;l<9;l++){
								for(int m=0;m<9;m++){
									board_copy[l][m] = board[l][m];
								}
							}
						}
					}
				}
				return 0;
			}
		}
	}
	
	return 0;
}


							
							



