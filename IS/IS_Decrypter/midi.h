#pragma once

/////////////////////////////////////////////
// Stephen Pretto  Korea University  0Day
// Implements a decrypter tool to find the message hidden in midi files
// Prints the results

#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <vector>
#include <string>
  
using namespace std; 
  
class midi
{ 
private:  
	std::vector<string> decode; //Stores the letter values of each note into a string 
	int numbernotes; //The number of read notes (unused)
	string infname; //Input file name
	ifstream input; //Input stream
public: 
    void parsexml(string);  
	void process();
    void results();
	midi();
	~midi(void);
}; 
  
