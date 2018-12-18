#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>
#include "piglatin.h"

using namespace std;

int findFirstVowel(const char word[]){
	char vowels[] = "aeiouy";
	
	for(int i =0 ; i <(signed)strlen(word); i++){
		for(int j=0; j<(signed)strlen(vowels); j++){
			if(i == 0 || i == (signed) strlen(word)-1){
				if(word[i] == vowels[j] && vowels[j] != 'y'){
					return i;
				}
			}else{
				if(word[i] == vowels[j]){
					return i;
				}
			}
		}
	}
	return -1;
}

void translateWord(const char english[], char piglatin[]){
	//Find the position of the first vowel
	int A = findFirstVowel(english);

	//Length of the word
	int word_length = (signed)strlen(english);

	char end[] = "way";

	if(A == 0){
		//Copy the word over
		for(int i = 0; i<word_length ; i++){
			piglatin[i] = english[i];
		}

		//Add "way" to the end

		for(int i=word_length; i<=word_length+3; i++){
			// <= to copy the '\0' too
			piglatin[i] = end[i-word_length];
		}
		return;
	}
		

	if(A != -1){
		for(int i = A; i<word_length; i++){
			if(i==A && isupper(english[i-A])){
				piglatin[i-A] = toupper(english[i]);
			}else{
				piglatin[i-A] = tolower(english[i]);
			}
		}

		//Add the front of the word to the end
		for(int i = 0; i<A;i++){
			piglatin[word_length-A+i] = tolower(english[i]);
		}

		//add "ay"
		for(int i=1;i<4;i++){
			piglatin[word_length+i-1] = end[i];
		}

		return;
	}

	if(A==-1){
		//Copy word over
		for(int i = 0; i< word_length; i++){
			piglatin[i] = english[i];
		}
		
		//Add "ay" to the end if not digit
		if(isdigit(english[0])){
			piglatin[word_length] ='\0';
		}else{
			for(int i = word_length;i<=word_length+2;i++){
				piglatin[i] = end[i-word_length+1];
			}
		}
		return;
	}
	return;
}


void translateStream(istream &input, ostream &output){
	ifstream reader;
	char piglatin[128];
	char word[64];

	if(getWord(input,word)){
		translateWord(word,piglatin);
		output << piglatin;
	}else{
		if(!input.eof()){
			output << word;
		}
	}

	while(!input.eof()){
		translateStream(input, output);
	}

	return;
}

bool getWord(istream &input, char word[]){
	int count = 0;
	char ch;

	input.get(ch);
	if(input.eof()){
		return 0;
	}

	if(!isalnum(ch)){
		word[count] = ch;
		word[count+1] = '\0';
		return 0;
	}

	while(!input.eof()){

		if(isalnum(ch)){
			word[count] = ch;
			count++;
			input.get(ch);

		}else if(!isalnum(ch)){
			input.putback(ch);
			word[count] = '\0';
			return 1;
		}
	}
}
