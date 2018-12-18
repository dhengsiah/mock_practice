#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

#include "braille.h"

int encode_character(char ch, char braille[]){
	char b_alphabet[][7] = {"0.....","00....","0..0..","0..00.",
						  "0...0.","00.0..","00.00.","00..0.",
						  ".0.0..",".0.00.","0.0...","000...",
						  "0.00..","0.000.","0.0.0.","0000..",
						  "00000.","000.0.",".000..",".0000.",
						  "0.0..0","000..0",".0.000","0.00.0",
						  "0.0000","0.0.00","......"};

	char b_punctuation[][7] = {".0..00",".0....",".00...","..0..0",".00.0.",".00..0",".00.00",".00.00"};
	
	char b_capital[] = ".....0";
	char b_digit[] = "..0000";

	char alphabet[] = "abcdefghijklmnopqrstuvwxyz ";
	char punctuation[] = ".,;-!?()";
	char digits[] = "12345679";

	//count the number of braille characters used
	int count=0;

	//Check if digit
	if(isdigit(ch)){
		count++;
		for(int i = 0; i<6; i++){
			braille[i] = b_digit[i];
		}
		if(ch == 0){
			for(int i = 0; i<7; i++){
				braille[BRAILLE_LENGTH+i] = b_alphabet[9][i];
			}
		}

		for(int i=0;i<(signed)strlen(digits) ; i++){
			if(ch == digits[i]){
				count++;
				for(int j = 0; j<7; j++){
					braille[BRAILLE_LENGTH+j] = b_alphabet[i][j];
				}
				return count*BRAILLE_LENGTH;
			}
		}

	//Check if punctuation
	}else if(ispunct(ch)){
		for(int i = 0;i<(signed)strlen(punctuation);i++){
			if(ch == punctuation[i]){
				count++;
				for(int j = 0 ; j<7; j++){
					braille[j] = b_punctuation[i][j];
				}
				return count*BRAILLE_LENGTH;
			}
		}
	}else{
		//Check if uppercase
		if(isupper(ch)){
			count++;
			for(int i =0;i<7;i++){
				braille[i] = b_capital[i];
			}
		}
		for(int i =0; i<(signed)strlen(alphabet);i++){
			if(tolower(ch) == alphabet[i]){
				for(int j=0;j<7;j++){
					braille[BRAILLE_LENGTH*count+j] = b_alphabet[i][j];
				}
				count++;
				return count*BRAILLE_LENGTH;
			}
		}
	}
	return -1;
}

void encode(char plaintext[], char braille[]){
	//Terminate recursion when the end is reached
	if(plaintext[0] == '\0'){
		return;
	}

	//Encode the character
	int size = encode_character(plaintext[0],braille);

	//Call the recursion based on how many "characters used"
	encode(&plaintext[1],&braille[size]);	
	return;
}

void print_braille(char plaintext[], ostream &output){
	//Convert plaintext into braille
	char braille[512];

	encode(plaintext,braille);
	
	//Count the number of braille character used
	int total = (signed)strlen(braille)/6;
	
	for(int i =0;i<total;i++){
		output << braille[0+6*i]<<braille[3+6*i] <<" ";
	}

	output << endl;
	for(int i =0;i<total;i++){
		output << braille[1+6*i]<<braille[4+6*i]<< " ";
	}
	output << endl;

	for(int i =0;i<total;i++){
		output << braille[2+6*i]<<braille[5+6*i]<< " ";
	}
	output << endl;

	for(int i=0;i<total;i++){
		if(isupper(plaintext[i]) || isdigit(plaintext[i])){
			output<< "   ";
		}
		output << plaintext[i] << "  ";
	}
	output << endl;
	return;
}

