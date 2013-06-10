#include <iostream>
#include "MPUINT.H"

class WordInt 
{
public:
	WordInt();
	~WordInt();

	void printArray(int* intArray);
	int* intArray;
	int Match(char c);
	int size;
	mpuint GetMpuint(std::string c, int int_len, int* char_len);
	int* Converter(std::string str);
	int* Converter(mpuint);
	static std::string mpuintToString(mpuint in);
	static mpuint ReConverter(int* in, int size, int mpusize);
	static int sizeOfMpuintToIntArr(mpuint);
};
