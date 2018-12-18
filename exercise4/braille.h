#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

#define BRAILLE_LENGTH 6

//Main functions

int encode_character(char ch, char braille[]);

void encode(char plaintext[], char braille[]);

void print_braille(char plaintext[], ostream &out);
