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
	/*���� process �κп��� ��ü �޼����� ���� ������ �ϳ��� char�� �ٷ�� ��ó�� ����ϰ��ִ�.
	process �Լ��� ȣ������ �ʰ� ������ note�� �׳� int�� �迭�� ������ encoder ��Ʈ���� midi file��
	�Է��ϱ� ������ int*�� ���� �� �ִ�.
	���� encoder���� rsa ��ȣȭ �κ��� ��ȣȭ ����� ���� �����Ǿ� �������� #include�� RSAEncrypter class�� �����ϸ�
	�ٷ� ��� �����ϴ�.
	������ WordtoInt class���� GetMpuint, Converter method�ε� �̰��� �ݴ�� �����ϴ� �κ��� �����Ǿ� ���� �ʴ�.
	100����, 1000������ �����͸� ��� ó���ϴ� �κ��̹Ƿ� �̺κи� ������ �Ųٷ� �����ϸ� �ɵ�
*/

	//decode.process();
    decode.results(); 

  	return 0;
}

