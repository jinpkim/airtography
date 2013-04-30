#pragma once
class RSAEncrypter
{
private:
	int m_p, m_q;
	long inline RSAEncrypter::m_N() { return m_p * m_q; };
	long inline RSAEncrypter::m_pi_N() { return (long)((m_p-1)*(m_q-1)); };
	long m_publicKey;
	long m_extededEuclid;

	int RSAEncrypter::gcd(long a, long b);
	long RSAEncrypter::getPublicKey_e(long pi_N);
	long RSAEncrypter::extendedEuclid(long e, long pi_N);
	long RSAEncrypter::expX_modN(long X, long exp, long N);
	int RSAEncrypter::expX_modN(int X, int exp, int N);

public:
	RSAEncrypter(void);
	~RSAEncrypter(void);

	void RSAEncrypter::PrepareRSA(int p, int q, long publicKey);
	char* RSAEncrypter::Encrypt(char* val);
	char* RSAEncrypter::Decrypt(char* val);
	int* RSAEncrypter::Encrypt(int* val, int size);
	int* RSAEncrypter::Decrypt(int* val, int size);

};

