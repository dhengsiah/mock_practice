#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

#include "words.h"

void reverse(char str1[], char str2[]){
	int end = strlen(str1);

	for(int i = 0; i < end; i++){
		str2[i] = str1[end-i-1];
	}

	str2[end] = '\0';
	return;
}

bool compare(char one[], char two[]){
	bool flag;

	char a;
	char b;

	if(!isalpha(one[0]) && one[0] != '\0'){
		flag = compare(&one[1],&two[0]);

		if(flag == 1){
			return 1;
		}else{
			return 0;
		}
	}else if(!isalpha(two[0]) && two[0] != '\0'){
		flag = compare(&one[0],&two[1]);

		if(flag == 1){
			return 1;
		}else{
			return 0;
		}
	}

	if(one[0] == '\0' && two[0] == '\0'){	
		return 1;
	}else if(one[0] == '\0' && two[0] != '\0'){
		return 0;
	}else if(one[0] != '\0' && two[0] == '\0'){
		return 0;
	}


	a=toupper(one[0]);
	b=toupper(two[0]);

	if(a!=b){
		return 0;
	}

	if(a == b){
		flag = compare(&one[1],&two[1]);
		
		if(flag==1){
			return 1;
		}else{
			return 0;
		}
	}

/*

cout << one[0] << " & " << two[0] << endl;
	if(!isalpha(one[0]) && one[0] != '\0'){
		while(one[1] != '\0'){
			flag = compare(&one[1],&two[0]);
			if(flag == 1){
				return 1;
			}else{
				return 0;
			}
		}
		if(one[1] == '\0' && two[1] == '\0'){
			return 1;
		}
	}else if(!isalpha(two[0]) && two[0] != '\0'){
		while(two[1] != '\0'){
			flag = compare(&one[0],&two[1]);
			if(flag ==1){
				return 1;
			}else{
				return 0;
			}
		}
	}

	if(one[0] == '\0' && two[0] != '\0'){
		cout << "hi" << endl;
		return 0;
	}else if(one[0] != '\0' && two[0] == '\0'){
		cout<< "hi2"<< endl;
		return 0;
	}else if(one[0] == '\0' && two[0] == '\0'){
		return 1;
	}
	
	a=toupper(one[0]);
	b=toupper(two[0]);

	if(a!= b && isalpha(a) && isalpha(b)){
		cout << "Hi3" <<endl;
		return 0;
	}

	if(a == b || (!isalpha(a) && !isalpha(b))){
		while(one[1] != '\0' && two[1] != '\0'){
			flag = compare(&one[1],&two[1]);

			if(flag == 1){
				return 1;
			}else{
				return 0;
			}
		}
	}
*/

	return 0;
}

bool palindrome(char sentence[]){
	int length = (signed)strlen(sentence);
	char temp[length];	
	reverse(sentence, temp);
	return compare(sentence,temp);
}

bool anagram(char str1[], char str2[]){
	//Lengths to initialise sorted arrays
	int a = strlen(str1);
	int b = strlen(str2);

	char sorted1[a];
	char sorted2[b];

	sort(str1,sorted1);
	sort(str2,sorted2);
	return compare(sorted1,sorted2);
}

void sort(char string[],char sorted[]){
//	int length =0;
	int string_length = strlen(string);
	char* temp[string_length];

	for(int i = 0; i<(signed)strlen(string); i++){
		temp[i] = &string[i];
	}

	for(int j =0;j<(signed)strlen(string);j++){
	//Pick first non-sorted character
	char a;
	int index;
		for(int i = 0; i<(signed)strlen(string); i++){
			if(temp[i] != NULL){
				a = string[i];
				index = i;
				break;
			}
		}
		//Get the biggest character as '\0' is the smallest ascii char
		for(int i = 0; i<(signed)strlen(string);i++){
			if(temp[i] != NULL){
				//Checks whether the a we had was the biggest character
				if(toupper(a)> toupper(string[i])){
					a = string[i];
					index = i;
				}
			}
		}
		//Place the list in descending order
		sorted[j] = a;

		//Indicate that the character has been "sorted"
		temp[index] = NULL;
			
	}

	return;
}
