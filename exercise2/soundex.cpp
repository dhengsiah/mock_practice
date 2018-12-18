#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

#include "soundex.h"

void encode(const char surname[],char soundex[]){
	bool flag;
	char temp;

	int i=0;
	int j=0;

	//Loop through while 4 letters hasn't been encoded and not at end of the word
	while(surname[i]&&j<4){

		//Encode the first letter by copying it over.
		if(i == 0){
			soundex[j] = surname[i];
			j++;
			i++;

		}else{
			//Check letter to see whether should be ignored
			flag = check_letter(surname[i]);
			if(flag == 0){
				i++;
			}else{
				//Encode the letter if not "aehiouwy"
				temp = encode_character(surname[i]);
				i++;
				//Check whether adjacent characters have the same digit. If same, ignore.
				if(temp != soundex[j-1]){
					soundex[j] = temp;
					j++;
				}
			}
		}
	}


	//If less than 4 letters encoded, fill the remaining with 0s
	while(j<4){
		soundex[j] = '0';
		j++;
	}
	//Terminate string with null-character at the end.
	soundex[j] = '\0';
	return;
}		

bool compare(char one[], char two[]){

	//Keeps track of recursion
	bool flag;

	if(strlen(one) != strlen(two)){
		cerr << "Soundex code lengths do not match" << endl;
		return 0;
	}
	
	//If reached the end of the string to check, terminate and return true if no failure
	if(one[0] == '\0'){
		return 1;
	}
	//If the characters differ, return false and terminate recursion
	if(one[0] != two[0]){
		return 0;
	}
	
	//As long as characters match, call compare on next 2 characters until one of the two above cases are reached
	if(one[0] == two[0]){
		return compare(&one[1],&two[1]);


/*		flag = compare(&one[1],&two[1]);


		if(flag == 1){
			return 1;
		}else{
			return 0;
		}*/
	}
	cerr << "Error" << endl;
	return 0;
}

int count(char surname[], char sentence[]){
	
	//Pointer to hold word to compare
	char* word;
	char e_word[5];

	//Holds the soundex of base surname
	char base_word[5];

	//Counts the number of words that matchs
	int count = 0;

/*Could have done: 
	int length = (signed) strlen(sentence);
	char temp_sentence[length];
	*/

	char temp_sentence[1024];

	encode(surname,base_word);

	//Split sentence into words

	//Copies sentence into temp_sentence as we are not allowed to manipulate it directly
	strcpy(temp_sentence,sentence);

	//Initialise the word with strtok
	word = strtok(temp_sentence, " ,.");

	//Encode the word to compare
	encode(word, e_word);
	
	if(compare(base_word,e_word)){
		count++;
	}
	
	//Call recursion on the same sentence
	while(word != NULL){
		word = strtok(NULL, " ,.");
		if(word != NULL){
			encode(word,e_word);
		}
		if(compare(base_word,e_word)){
			count++;
		}
	}

	return count;
}

bool check_letter(char letter){
	char vowels[] = "aehiou";
	for(int i = 0 ; i<(signed)strlen(vowels) ; i++){
		if(letter == vowels[i]){
			return 0;
		}
	}
	return 1;
}
char encode_character(char letter){
	char one[] = "bfpv";
	char two[] = "cgjkqsxz";
//	char three[] = "dt";

	for(int i = 0; i<(signed)strlen(one); i++){
		if(letter == one[i]){
			return '1';
		}
	}

	for(int i = 0; i<(signed)strlen(two); i++){
		if(letter == two[i]){
			return '2';
		}
	}

	if(letter == 'd' || letter == 't'){
		return '3';
	}

	if(letter == 'l'){
		return '4';
	}

	if(letter == 'm' || letter == 'n'){
		return '5';
	}

	if(letter == 'r'){
		return '6';
	}
	
	//Error code
	return '7';
}
