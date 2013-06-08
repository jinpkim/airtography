#include "midi.h"


midi::midi(void)
{
	numbernotes = 0;
}



midi::~midi(void)
{
}



void midi::parsexml(string file) 
{ 
	string value;
	string note ("Note=");
    infname = file; //Then open up the input with it 
	input.open(infname.c_str());
	while(!input.eof())
	{
		input >> value;
		if (value.find(note) != string::npos) 
		{
			string notevalue ("");
			for (unsigned int i = 0; i < value.length(); i++)
			{
				if (isdigit(value[i]))
					notevalue += value[i];
			}
			decode.push_back(notevalue);
			numbernotes++;
		} 
	}
} 

void midi::results()
//Goes through the vector and prints each letter
{
	for (unsigned int i = 0; i < decode.size(); i++)
	{
		cout << decode.at(i);
	}
	cout << endl;
}
  
  
void midi::process()
{
	int last = 0;
	for(unsigned int i=0; i<decode.size(); ++i, ++last)
	{
		while((i%2)!= 0)
			++i;
		if(i >= decode.size()) break;
			decode[last] = decode[i];   
	}
	decode.resize(last);	
	
	for (unsigned int i = 0; i < decode.size(); i++) //These three assign new numeric values to three letters which conflict with the 0-9 number space
			if (decode.at(i) == "5")
				decode[i] = "155";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "2")
				decode[i] = "156";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "3")
				decode[i] = "157";	

	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "47")
				decode[i] = "0";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "48")
				decode[i] = "1";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "4")
				decode[i] = "2";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "14")
				decode[i] = "3";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "21")
				decode[i] = "4";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "31")
				decode[i] = "5";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "89")
				decode[i] = "6";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "9")
				decode[i] = "7";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "49")
				decode[i] = "8";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "56")
				decode[i] = "9";
			

	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "43")
				decode[i] = "A";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "53")
				decode[i] = "B";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "60")
				decode[i] = "C";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "70")
				decode[i] = "D";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "26")
				decode[i] = "E";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "27")
				decode[i] = "F";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "34")
				decode[i] = "G";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "17")
				decode[i] = "H";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "66")
				decode[i] = "I";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "106")
				decode[i] = "J";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "44")
				decode[i] = "K";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "87")
				decode[i] = "L";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "76")
				decode[i] = "M";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "35")
				decode[i] = "N";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "24")
				decode[i] = "O";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "67")
				decode[i] = "P";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "155")
				decode[i] = "Q";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "45")
				decode[i] = "R";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "94")
				decode[i] = "S";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "77")
				decode[i] = "T";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "84")
				decode[i] = "U";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "85")
				decode[i] = "V";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "41")
				decode[i] = "W";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "51")
				decode[i] = "X";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "58")
				decode[i] = "Y";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "68")
				decode[i] = "Z";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "75")
				decode[i] = "a";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "55")
				decode[i] = "b";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "62")
				decode[i] = "c";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "102")
				decode[i] = "d";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "22")
				decode[i] = "e";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "80")
				decode[i] = "f";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "90")
				decode[i] = "g";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "97")
				decode[i] = "h";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "107")
				decode[i] = "i";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "63")
				decode[i] = "j";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "64")
				decode[i] = "k";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "71")
				decode[i] = "l";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "54")
				decode[i] = "m";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "103")
				decode[i] = "n";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "32")
				decode[i] = "o";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "81")
				decode[i] = "p";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "13")
				decode[i] = "q";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "156")
				decode[i] = "r";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "72")
				decode[i] = "s";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "61")
				decode[i] = "t";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "104")
				decode[i] = "u";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "42")
				decode[i] = "v";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "82")
				decode[i] = "w";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "20")
				decode[i] = "x";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "157")
				decode[i] = "y";
	for (unsigned int i = 0; i < decode.size(); i++)
			if (decode.at(i) == "10")
				decode[i] = "z";
}
 