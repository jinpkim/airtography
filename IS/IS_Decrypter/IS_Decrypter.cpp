// IS_Decrypter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "midi.h"
#include "../IS/RSA.H"
#include "../IS/MPUINT.H"
#include "../IS/RSAEncrypter.h"
#include "../IS/WordtoInt.h"

const unsigned int MAX_MPUINT_LEN = 32;
const char *rsa_d = "3944468182306490129890668128064166282888079664881759058485822932535889194050612552881100935547024572480766043979477430280352683150981569778761095649256861";
const char *rsa_e = "2059401299394647702106117656899229530707170303380700778668875719255199099359609820845614887146444406353484725021121780926979946947620426792867529081508741";
const char *rsa_n = "5976422441365186438016701355398741256152489884652994504696330715375530622839572107040284724219589165254936455575947087089199768690286896908774443748874051";


int main(int argc, char *argv[]) 
{
	mpuint e(MAX_MPUINT_LEN), n(MAX_MPUINT_LEN), encrypt(MAX_MPUINT_LEN), decrypt(MAX_MPUINT_LEN);

    string file = argv[1]; 
    midi decode; 
      
    decode.parsexml(file);
	/*
	���� process �κп��� ��ü �޼����� ���� ������ �ϳ��� char�� �ٷ�� ��ó�� ����ϰ��ִ�.
	process �Լ��� ȣ������ �ʰ� ������ note�� �׳� int�� �迭�� ������ encoder ��Ʈ���� midi file��
	�Է��ϱ� ������ int*�� ���� �� �ִ�.
	���� encoder���� rsa ��ȣȭ �κ��� ��ȣȭ ����� ���� �����Ǿ� �������� #include�� RSAEncrypter class�� �����ϸ�
	�ٷ� ��� �����ϴ�.
	������ WordtoInt class���� GetMpuint, Converter method�ε� �̰��� �ݴ�� �����ϴ� �κ��� �����Ǿ� ���� �ʴ�.
	100����, 1000������ �����͸� ��� ó���ϴ� �κ��̹Ƿ� �̺κи� ������ �Ųٷ� �����ϸ� �ɵ�
	*/

	decode.process();
    //decode.results(); 
	int* midiArr = decode.ConvertToIntA();
	encrypt = WordInt::ReConverter(midiArr, decode.GetInputSize(), MAX_MPUINT_LEN);

	//
	/*char *c = new char[512];
	cout << encrypt.edit(c) << endl;*/
	//


	e.scan(rsa_e); n.scan(rsa_n);
	EncryptDecrypt(decrypt, encrypt, e, n);
	std::string originStr = WordInt::mpuintToString(decrypt);

	cout << originStr << endl;

  	return 0;
}

