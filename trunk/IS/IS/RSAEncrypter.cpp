#include "RSAEncrypter.h"

#include<cmath>
#include<iomanip>
#include<time.h>

//큰 소수 두개.
#define LPRIME_1 1175003
#define LPRIME_2 1249921

RSAEncrypter::RSAEncrypter(void)
{
}


RSAEncrypter::~RSAEncrypter(void)
{
}



int RSAEncrypter::gcd(long a, long b){
	long r =0;
	if(b>a){
		long tmp = a;
		a = b;
		b = tmp;
	}
	r = a%b;
	while(r>0){
		a = b;
		b = r;
		r = a%b;
	}
	return b;	
}

long RSAEncrypter::getPublicKey_e(long pi_N){
	long e=0;
	long tmpGcd;
	while(1){
		e = (long)(rand()%pi_N+1);
		if(e == 1) 
			continue;
		tmpGcd = gcd(e, pi_N);
		if(tmpGcd == 1)
			break;
	}
	return e;
}

//확장 유클리드알고리즘. fine private key
long RSAEncrypter::extendedEuclid(long e, long pi_N){
	long E, N, q, r,s,t,u;
	E = e;
	N = pi_N;
	t = 0; u = 1;
	
	while(E!=1)
	{
		q = N/E;
		r = N - E*q;
		s = t - u*q;
		N = E;
		E = r;
		t = u;
		u = s;
	}
	if(u < 0)
		u = u+pi_N;
	return u;
}

//암호화 또는 복호와의 핵심 (M^e(mod N)  or C^e(mod N) )
long RSAEncrypter::expX_modN(long X, long exp, long N){
	long tmp=1;
	while(exp!=0){
		while(exp%2 ==0){
			exp = exp/2;
			X = (X*X)%N;
		};
		exp--;
		tmp = (tmp*X)%N;
	}
	return tmp;
}


void RSAEncrypter::PrepareRSA(int p, int q, long publicKey){
	m_p = p;
	m_q = q;
	m_publicKey = publicKey;
	m_extededEuclid = extendedEuclid(m_publicKey, RSAEncrypter::m_pi_N());

	return;
}

char* RSAEncrypter::Encrypt(char* val){
	return 0;
}

char* RSAEncrypter::Decrypt(char* val){
	return 0;
}
