#include <iostream>

using namespace std;

#include "substring.h"

bool is_prefix(char s1[], char s2[]){
	bool k;

	if(s1[0] == '\0'){
		return 1;
	}

	if(s1[0] == s2[0]){
//	cout <<"Letters are: " << s1[0] << " & " << s2[0]<< endl;
		k=is_prefix(&s1[1],&s2[1]);
		return k;
	}

	return 0;
}
/*
bool is_prefix(char s1[], char s2[]){
	bool k;

	if(s1[0] == '\0'){
		return 1;
	}

	if(s1[0] == s2[0]){
//	cout <<"Letters are: " << s1[0] << " & " << s2[0]<< endl;


		k=is_prefix(&s1[1],&s2[1]);

		if(k==1){
			return 1;
		}

		if(k==0){
			return 0;
		}
	}

	return 0;
}
*/
int substring_position(char s1[], char s2[]){
	int count;
	bool k;

	if(s1[0] == '\0'){
		return 0;
	}


	//Checks initially
	k=is_prefix(&s1[0],&s2[0]);

	if(k==1){
		return 0;
	}
	
	while(s2[1] != '\0'){
		count = substring_position(&s1[0],&s2[1]);

		if(count == -1){
			return -1;
		}

		return count+1;
	}
	
	if(k==0 && s2[1] == '\0'){
		return -1;
	}
	
	return -1;
}
