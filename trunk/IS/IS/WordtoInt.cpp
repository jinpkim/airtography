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

// make string to mpuint, char_len is output
mpuint WordInt::GetMpuint(std::string c, int int_len, int *char_len)
{
	int clen = c.length();
	*char_len = clen;
	mpuint ret(int_len);
	ret = 0;
	
	for (int i = 0; i < clen; ++i)
	{
		//3�ڸ��� ������ char���� ���� ���·� ��
		ret *= 1000;
		ret += (int)c[i];
	}

	return ret;
}

// make string to mpuint, char_len is output
std::string WordInt::mpuintToString(mpuint in)
{
	int ti = 0;
	std::string ret = "";
	mpuint temp = in;

	while(in > 0)
	{
		temp = in;
		temp %= 1000;
		in /= 1000;
		ti = temp.value[0];
		ret += (char)ti;
	}
	
	std::reverse(ret.begin(), ret.end());
	return ret;
}


// convert mpuint to int*(this can conver to midi)
int* WordInt::Converter(mpuint in)
{
	int *out;
	mpuint t_mpu = in;
	int size = WordInt::sizeOfMpuintToIntArr(in)/2;
	size += WordInt::sizeOfMpuintToIntArr(in)%2 == 0 ? 0 : 1;
	out = new int[size];

	//mpuint ������ ū integer�� 2�ڸ��� ������ ��� int[]�� �ִ´�.
	for (int i = 0; i < size; ++i) {
		t_mpu = in;
		t_mpu %= 100;
		in /= 100;
		out[size-1-i] = t_mpu.value[0];
	}

	this->intArray = out;
	this->size = size;

	return out;
}

mpuint WordInt::ReConverter(int* in, int size, int mpusize)
{
	mpuint ret(mpusize);
	ret = in[0];

	for (int i = 1; i < size; ++i)
	{
		ret *= 100;
		ret += in[i];

		char c[256];
		ret.edit(c);
	}

	return ret;
}

int WordInt::sizeOfMpuintToIntArr(mpuint in)
{
	char c[512];
	std::string str = in.edit(c);

	return str.length();
}