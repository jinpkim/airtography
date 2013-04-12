#include <iostream>

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
};