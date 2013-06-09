// IS_Decrypter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "midi.h"
#include "../IS/MPUINT.H"


int main(int argc, char *argv[]) 
{
    string file = argv[1]; 
    midi decode; 
      
    decode.parsexml(file);
	/*현재 process 부분에서 전체 메세지를 따로 나누어 하나의 char를 다루는 것처럼 취급하고있다.
	process 함수를 호출하지 않고 각각의 note를 그냥 int형 배열에 넣으면 encoder 파트에서 midi file에
	입력하기 직전의 int*를 얻을 수 있다.
	현재 encoder에서 rsa 암호화 부분은 복호화 기능이 전부 구현되어 있음으로 #include로 RSAEncrypter class만 참조하면
	바로 사용 가능하다.
	문제는 WordtoInt class에서 GetMpuint, Converter method인데 이것을 반대로 적용하는 부분은 구현되어 있진 않다.
	100단위, 1000단위로 데이터를 끊어서 처리하는 부분이므로 이부분만 적당히 거꾸로 구현하면 될듯
*/

	//decode.process();
    decode.results(); 

  	return 0;
}

