#ifndef MERSENNETWISTER_H
#define MERSENNETWISTER_H

#include <climits>
#include <cstdio>
#include <ctime>

// Richard J. Wagner's Mersenne Twister (MersenneTwister.h, pre-1.0 release):
// uint32 is unsigned long, seed(uint32) uses Knuth's 69069 initialization and
// seed() reads the state straight from /dev/urandom.
class MTRand
{
public:
    typedef unsigned long uint32;

    enum { N = 624 };
    enum { SAVE = N + 1 };

protected:
    enum { M = 397 };

    uint32 state[N];
    uint32* pNext;
    int left;

public:
    MTRand() { seed(); }

    double randExc() { return double(randInt()) * (1.0 / 4294967296.0); }
    double randExc(const double& n) { return randExc() * n; }
    uint32 randInt();

    void seed(uint32 oneSeed);
    void seed();

protected:
    void reload();
    uint32 hiBit(const uint32& u) const { return u & 0x80000000UL; }
    uint32 loBit(const uint32& u) const { return u & 0x00000001UL; }
    uint32 loBits(const uint32& u) const { return u & 0x7fffffffUL; }
    uint32 mixBits(const uint32& u, const uint32& v) const { return hiBit(u) | loBits(v); }
    uint32 twist(const uint32& m, const uint32& s0, const uint32& s1) const
    {
        return m ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? 0x9908b0dfUL : 0x0UL);
    }
    static uint32 hash(time_t t, clock_t c);
};

inline MTRand::uint32 MTRand::randInt()
{
    if (left == 0)
        reload();
    --left;

    register uint32 s1;
    s1 = *pNext++;
    s1 ^= (s1 >> 11);
    s1 ^= (s1 << 7) & 0x9d2c5680UL;
    s1 ^= (s1 << 15) & 0xefc60000UL;
    return (s1 ^ (s1 >> 18));
}

inline void MTRand::seed(uint32 oneSeed)
{
    register uint32* s;
    register int i;
    for (i = N, s = state; i--;
         *s = oneSeed & 0xffff0000,
         *s++ |= ((oneSeed *= 69069U)++ & 0xffff0000) >> 16,
         (oneSeed *= 69069U)++)
    {
    }
    reload();
}

inline void MTRand::seed()
{
    FILE* urandom = fopen("/dev/urandom", "rb");
    if (urandom)
    {
        register uint32* s = state;
        register int i = N;
        register bool success = true;
        while (success && i--)
            success = fread(s++, sizeof(uint32), 1, urandom);
        fclose(urandom);
        if (success)
        {
            reload();
            return;
        }
    }
    seed(hash(time(NULL), clock()));
}

inline void MTRand::reload()
{
    register uint32* p = state;
    register int i;
    for (i = N - M; i--; ++p)
        *p = twist(p[M], p[0], p[1]);
    for (i = M; --i; ++p)
        *p = twist(p[M - N], p[0], p[1]);
    *p = twist(p[M - N], p[0], state[0]);

    left = N, pNext = state;
}

inline MTRand::uint32 MTRand::hash(time_t t, clock_t c)
{
    static uint32 differ = 0;

    uint32 h1 = 0;
    unsigned char* p = (unsigned char*)&t;
    for (size_t i = 0; i < sizeof(t); ++i)
    {
        h1 *= UCHAR_MAX + 2U;
        h1 += p[i];
    }
    uint32 h2 = 0;
    p = (unsigned char*)&c;
    for (size_t j = 0; j < sizeof(c); ++j)
    {
        h2 *= UCHAR_MAX + 2U;
        h2 += p[j];
    }
    return (h1 + differ++) ^ h2;
}

#endif
