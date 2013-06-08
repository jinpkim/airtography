// IS_Decrypter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "midi.h"


int main(int argc, char *argv[]) 
{
    string file = argv[1]; 
    midi decode; 
      
    decode.parsexml(file);
	decode.process();
    decode.results(); 

  	return 0;
}

