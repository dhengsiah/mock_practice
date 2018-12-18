#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

//Main functions
int findFirstVowel(const char word[]);

void translateWord(const char english[], char translated[]);

void translateStream(istream &input, ostream &output);

bool getWord(istream &input, char word[]);
