#include <utility>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "prime_rand.h"

std::vector<char> calc_primes_sieve(unsigned long max);
unsigned long find_fa_sieve(std::vector<char>& sieve, unsigned long step);
unsigned long cross_lfa_sieve(std::vector<char>& sieve, unsigned long step);

unsigned long prime_rand(unsigned long max) {
    srand(time(NULL));
    std::vector<char> sieve = calc_primes_sieve(max);
    unsigned long size = sieve.size();
    return cross_lfa_sieve(sieve, (rand() % size / 2) + size / 2 - 1);
}

std::vector<unsigned long> prime_rands(unsigned long max, unsigned long count) {
    srand(time(NULL));
    std::vector<char> sieve = calc_primes_sieve(max);
    unsigned long size = sieve.size();
    std::vector<unsigned long> results(count);
    for (unsigned long i = 0; i < count; i++) {
        unsigned long step = (rand() % size / 2) + size / 2 - 1;
        results[i] = cross_lfa_sieve(sieve, step);
    }
    return results;
}

unsigned long find_fa_sieve(std::vector<char>& sieve, unsigned long step) {
    for (unsigned int i = step + 1; i < sieve.size(); i++)
        if (sieve[i])
            return i;
    return sieve.size();
}

unsigned long cross_lfa_sieve(std::vector<char>& sieve, unsigned long step) {
    for (unsigned int i = step; i >= 0; i--)
        if (sieve[i]) {
            sieve[i] = 0;
            return i;
        }
    return sieve.size();
}

std::vector<char> calc_primes_sieve(unsigned long max) {
    std::vector<char> sieve(max, 1);
    unsigned long fa = 2;
    while (fa < max)
    {

        unsigned long i = fa * fa;
        while (i < max)
        {
            sieve[i] = 0;
            i += fa;
        }
        fa = find_fa_sieve(sieve, fa);
    }
    return sieve;
}