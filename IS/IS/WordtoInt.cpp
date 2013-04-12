#include "WordtoInt.h"

WordInt::WordInt()
{
	std::cout << "WordInt Object is made" << std::endl;
}

WordInt::~WordInt()
{
	std::cout << "WordInt Obeject is destructed" << std::endl;
}
int* WordInt::Converter(std::string str)
{	
	size = str.length();
	char *word = new char[size];
	int* arr = new int[size];
	strncpy(word, str.c_str(), size);
	for(int i=0;i<size;i++)
	{
		if(Match(word[i]) == -1)
			arr[i] = 31; // If it is impossible to match -> value is just 31(meaningless value)
		else
			arr[i] = Match(word[i]); // possible -> value return (with ASCII)
	}
	WordInt::intArray = arr;
	return arr;
	
}

int WordInt::Match(char c)
{
	int mat;
	if((int)c >= 32 && (int)c <= 125)
	{
		mat = (int)c - 32; ///// 32~125 -> 0~93
		return mat+10;	// to Make 'space' sound ///// 0~93 -> 10~103
	}
	else
	{
		fprintf(stderr, "Impossible to Match\n");
		return -1;
	}
}

void WordInt::printArray(int* a)
{
	for(int i=0;i<size;i++)
	{
		std::cout << a[i] << std::endl;
	}
}