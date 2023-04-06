#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelp(int length, string str, string floats, const set<std::string>& dict, set<std::string>& valid, int dash ); 


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    unsigned int length = 0;

    std::set<std::string> valid; 
		string floats = floating; 
		int dashes = 0; 
		for(int i = 0; i < in.size(); i++){
			if(in[i] == '-')
				dashes++; 
		}

    wordleHelp(length, in, floats, dict, valid, dashes); 

    return valid; 

}

// Define any helper functions here
void wordleHelp(int length, string str, string floats, const set<std::string>& dict, set<std::string>& valid, int dash)
{
		
	//base case  
		if(str.find('-') == string::npos){
			if(dict.find(str) != dict.end()) //check if is a valid English word
       	valid.insert(str);
			return; 
		}
		//check current position (length), 
	if(str[length] != '-')
		wordleHelp(length+1, str, floats, dict, valid, dash); // recurse for each spot

			//go through each floating character 
		// unsigned int dashes = count(str.begin(), str.end(), '-'); 
		
	else if(dash == floats.length()){
				int float_size = floats.length(); 
				for(int i = 0; i < float_size; i++){
					//replace the string at postion length with float 
					str[length] = floats[i];	
					string floater = floats.substr(0,i) + floats.substr(i+1, floats.size());//makes a new float string without temp
					dash--; 
					wordleHelp(length+1, str, floater, dict, valid, dash); // recurse for each spot
					str[length] = '-'; //remove the additon made	
					dash++;
				}
			}
			// return;  
		else{
			for(char c = 'a'; c <= 'z'; ++c){
					str[length] = c; 
					dash--; 
					int idx = floats.find(c);  
					if( idx != string::npos) {// if c in floats
						string floater = floats.substr(0,idx) + floats.substr(idx+1, floats.length());//makes a new float string without temp
						wordleHelp(length+1, str, floater, dict, valid, dash); // recurse for each spot
					}
					else
						wordleHelp(length+1, str, floats, dict, valid, dash); // recurse for each spot

					str[length] = '-'; //remove the additon made	
					dash++;
				}
			}
		
	}


