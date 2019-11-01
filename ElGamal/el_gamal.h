#include <utility>

namespace ElGamal {
    struct ElGamalKeys
    {
    public:
        unsigned long p;
        unsigned long g;
        unsigned long y;
        unsigned long x;
        ElGamalKeys(unsigned long p, unsigned long g, unsigned long y, unsigned long x);
    };
    ElGamalKeys GenerateKeys(unsigned long max);
    std::pair<unsigned long, unsigned long> Encrypt(unsigned long source, unsigned long p, unsigned long g, unsigned long y);
    unsigned long Decrypt(std::pair<unsigned long, unsigned long> cipher, unsigned long p, unsigned long x);
};

inline ElGamal::ElGamalKeys::ElGamalKeys(unsigned long p, unsigned long g, unsigned long y, unsigned long x) {
    ElGamalKeys::g = g;
    ElGamalKeys::p = p;
    ElGamalKeys::y = y;
    ElGamalKeys::x = x;
}