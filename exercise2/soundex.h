#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

void encode(const char surname[],char soundex[]);

bool check_letter(char letter);

char encode_character(char letter);

bool compare(char one[],char two[]);

int count(char surname[],char sentence[]);
