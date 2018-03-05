#include "crypto.h"
#include "utils.h"

#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

Crypto::Crypto(std::string key){
    mKey       = key;
    mKeyLength = key.length();
}

Crypto::Crypto(size_t keyLength){
    mKeyLength = keyLength;
    generateKey();
}

void Crypto::generateKey(){
    for (int i = 0; i < mKeyLength; i++)
	mKey += (rand() % 26) + 97;
}

void Crypto::encrypt(std::string &rData){
    std::string encrypted_data = "";
    std::vector<bool> binary_character, binary_key, binary_result;
    
    char data_array[rData.length()];
    strcpy(data_array, rData.c_str());

    char key_array[mKey.length()];
    strcpy(key_array, mKey.c_str());
    
    for(int i = 0; i < sizeof(data_array); i++){
	binary_character = utils::toByte(std::to_string(data_array[i]));
	binary_key       = utils::toByte(std::to_string(key_array[i % sizeof(key_array)]));

	for(int j = 0; j < 4; j++)
	    binary_result.push_back(binary_character[j] ^ binary_key[j]); 
	
	std::cout << "binary:";
	for(auto n : binary_character)
	    std::cout << n;
	std::cout << std::endl;

	encrypted_data += utils::toHex(binary_result);
/*    
	// TODO delete section, just for debug purpuses
	std::cout << std::endl << "data:   ";
	for(auto n:binary_character)
	    std::cout << n;
	std::cout << std::endl << "key:  " << key_array[i % sizeof(key_array)] << " ";
	for(auto n:binary_key)
	    std::cout << n;
	std::cout << std::endl << "result: ";
	for(auto n:binary_result)
	    std::cout << n;
	std::cout << std::endl << "char: " << data_array[i] << "  ->  " << toChar(binary_result) << std::endl;
	std::cout << (int)data_array[i] << " " << (int)toChar(binary_result) << std::endl;
	//
*/
	binary_key.clear();
	binary_character.clear();
	binary_result.clear();
    }
    rData = encrypted_data;
}
