#include <iostream>
#include "MPUINT.H"

class WordInt 
{
public:
	WordInt();
	~WordInt();

	int* Converter(std::string str);
	void printArray(int* intArray);
	int* intArray;
	int Match(char c);
	int size;
	mpuint GetMpuint(std::string c, int int_len, int* char_len);
	int* Converter(mpuint, int);
};
