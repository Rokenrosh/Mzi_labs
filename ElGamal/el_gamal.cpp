#include <ctime>
#include <vector>
#include "el_gamal.h"
#include "prime_rand.h"
#include "../lib/BigIntegerLibrary.hh"

unsigned long powmod(unsigned long a, unsigned long b, unsigned long p);
unsigned long generator(unsigned long p);

ElGamal::ElGamalKeys ElGamal::GenerateKeys(unsigned long max) {
	unsigned long p = prime_rand(max);
	unsigned long g = generator(p);
	unsigned long x = (rand() % p) + 1;
	unsigned long y = modexp(BigInteger(g), BigUnsigned(x), BigUnsigned(p)).toUnsignedLong();
	return ElGamal::ElGamalKeys(p, g, y, x);
}

std::pair<unsigned long, unsigned long> ElGamal::Encrypt(unsigned long source, unsigned long p, unsigned long g, unsigned long y) {
	srand(time(NULL));
	unsigned long k = (rand() % p - 1) + 1;
	BigUnsigned p_bi(p), k_bi(k);
	unsigned long a = modexp(BigInteger(g), k_bi, p_bi).toUnsignedLong();
	unsigned long b = ((modexp(BigInteger(y), k_bi, p_bi) * BigUnsigned(source)) % p_bi).toUnsignedLong();
	return std::make_pair(a, b);
}

unsigned long ElGamal::Decrypt(std::pair<unsigned long, unsigned long> cipher, unsigned long p, unsigned long x) {
	BigUnsigned exp(p - 1 - x), p_bi(p);
	BigInteger res = modexp(BigInteger(cipher.first), exp, p_bi);
	return modexp(BigInteger(cipher.second) * res, 1, p_bi).toUnsignedLong();
}

unsigned long powmod(unsigned long a, unsigned long b, unsigned long p) {
	unsigned long res = 1;
	while (b)
		if (b & 1)
			res = (unsigned long)(res * 1ll * a % p), --b;
		else
			a = (unsigned long)(a * 1ll * a % p), b >>= 1;
	return res;
}

unsigned long generator(unsigned long p) {
	std::vector<unsigned long> fact;
	unsigned long phi = p - 1, n = phi;
	for (unsigned long i = 2; i * i <= n; ++i)
		if (n % i == 0) {
			fact.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		fact.push_back(n);

	for (unsigned long res = 2; res <= p; ++res) {
		bool ok = true;
		for (unsigned long i = 0; i < fact.size() && ok; ++i)
			ok &= powmod(res, phi / fact[i], p) != 1;
		if (ok)  return res;
	}
	return -1;
}